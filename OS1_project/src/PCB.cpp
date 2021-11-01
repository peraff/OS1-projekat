#include "PCB.h"
#include "mainSet.h"
#include "kersem.h"
#include "sleepL.h"

int PCB::posID=-1;

unsigned tsp;
unsigned tss;
unsigned tbp;

volatile int brojac = 20;
volatile int zahtevana_promena_konteksta = 0;

volatile PCB* running;

volatile Niz nizPCB;


PCB::PCB(Thread* myThread, StackSize stackSize, Time timeSlice){

	mojaVelicina=stackSize/sizeof(unsigned);
	mojaNit=myThread;
	this->kvant=timeSlice;
	asm cli;
	mojStek=new unsigned[mojaVelicina];
	this->id=++posID;
	asm sti;

	this->pokrenut=0;
	this->blokiran=0;
	this->zavrsio=0;
	this->istekloVreme=0;
	//postavljanje vrednosti na pocetni stek, prvo argument wrapper funkcije

	mojStek[mojaVelicina-1]=FP_SEG(mojaNit);
	mojStek[mojaVelicina-2]=FP_OFF(mojaNit);

	//mesto za callback funkciju wrapera -3 i -4

	mojStek[mojaVelicina-5]=0x200;  // I bit postavljen na 1

	mojStek[mojaVelicina-6]=FP_SEG(&(PCB::wrapper));   //PC
	mojStek[mojaVelicina-7]=FP_OFF(&(PCB::wrapper));

	//mesto za registre,random pocetne vrednosti

	//popunjavanje pocetne pcb strukture iz koje ce se izvuci sp i bp

	this->ss=FP_SEG(mojStek+mojaVelicina-16);
	this->sp=FP_OFF(mojStek+mojaVelicina-16);
	this->bp=sp;
	//lPCB.dodaj(this);

	asm cli
	nizPCB.dodaj(this,this->id);
	asm sti;
}

void interrupt timer(){	// prekidna rutina

	if (!zahtevana_promena_konteksta){
		brojac--;
		tick();
		//if(sleepLista.velicina()){
		if(!sleepLista.prazna()){
			sleepLista.azuriraj();
		}
	}
	if (brojac == 0 || zahtevana_promena_konteksta) {
		asm {
			// cuva sp
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}

		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;

		if(!running->zavrsio && !running->blokiran && running->zavrsio!=-1)
		Scheduler::put((PCB*)running);

		running= Scheduler::get();	// Scheduler



		if(running==0){
			running=(volatile PCB*)idlePCB;      //idlePCB definisan u mainSet i postavlja se na pocetku maina.
		}


		tsp = running->sp;
		tss = running->ss;
		tbp = running->bp;

		/*if(!running->kvant){
			brojac=-1;
		} else
		brojac = running->kvant;
		*/

		brojac= running->kvant ? running->kvant:-1;
		asm {
			mov sp, tsp   // restore sp
			mov ss, tss
			mov bp, tbp
		}
	}

	// poziv stare prekidne rutine koja se
     // nalazila na 08h, a sad je na 60h
     // poziva se samo kada nije zahtevana promena
     // konteksta – tako se da se stara
     // rutina poziva samo kada je stvarno doslo do prekida
if(!zahtevana_promena_konteksta){
	asm int 60h;
}

	zahtevana_promena_konteksta = 0;

}

void dispatch(){ // sinhrona promena konteksta    OVO NAPISATI U THREAD FAJLU
	asm cli;
	zahtevana_promena_konteksta = 1;
	timer();
	asm sti;
}

void PCB::wrapper(Thread* mojaNit){
	mojaNit->run();
	mojaNit->myPCB->zavrsio=1;
	//ubaciti metod koji budi sve niti koje cekaju na ovu nit
	PCB* tmp;
	while(!(mojaNit->myPCB->listaBlokiranih.prazna())){
		if((tmp=mojaNit->myPCB->listaBlokiranih.izbaciPrvi())!=0){
			tmp->blokiran=0;
			if(!tmp->zavrsio)
			Scheduler::put(tmp);
		}
	}
	dispatch();
}

PCB::~PCB(){
	if(mojStek) delete [] mojStek;
}

void PCB::start(){
	if(this->pokrenut) return;
	pokrenut=1;
	Scheduler::put(this);
}
