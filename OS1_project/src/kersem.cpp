#include"kersem.h"
#include "sleepL.h"
#include "PCB.h"

SleepLista sleepLista;

KernelSem::~KernelSem(){

	while(!blockList.prazna()){
			PCB* p=blockList.izbaciPrvi();
			sleepLista.izbaci(p); //izbaci ako ga ima ovde! Tj ako je ubacen, x!=0 znaci da je i u sleep listi inace za x=0 samo je u bloceked listi
			p->blokiran=0;
			if(!p->zavrsio)
			Scheduler::put(p);
		}
}

int KernelSem::wait(Time maxTimeToWait){

	//cout<<"WAIT "<<val<<endl;
	asm cli

	if(--val<0){
	//	cout<<"Blokira se"<<endl;
		block(maxTimeToWait);
	}
	if(running->istekloVreme){
	//	cout<<"Isteklo"<<endl;
		running->istekloVreme=0;
		asm sti
		return 0;
	}
	else {
	//	cout<<"Propusten"<<endl;
		asm sti
		return 1;
	}
}


int KernelSem::signal(int n){

	asm cli;

	int ret;

	if(n<0) {

		asm sti;
		return n;

	}else if(n==0){
			//cout<<"Standardni signal:"<<val<<endl;
			if(val++<0)
				deblock();
			ret=0;

	} else {
				// cout<<"signal(N)"<<endl;					//ako je n>0
				ret=deblock(n);   //U deblock inkrementiraj val za br odblokiranih niti i to vrati. Samo prodji kroz listu blokiranih na semaforu i odblokiraj n
		}						// niti (ako ima) i kroz globalnu listu prodji i izbaci sve te da ne budu vise tu.

	asm sti
	return ret;
}

void KernelSem::block(int x){
	running->blokiran=1;
	blockList.dodaj((PCB*)running);

	if(x){
	sleepLista.dodaj((PCB*)running, x, this);
	}

	dispatch();
	asm cli

}
void KernelSem::deblock(){
	if (!blockList.prazna()){

		PCB* p=blockList.izbaciPrvi();

		sleepLista.izbaci(p); //izbaci ako ga ima ovde! Tj ako je ubacen, x!=0 znaci da je i u sleep listi inace za x=0 samo je u bloceked listi
		p->blokiran=0;
		Scheduler::put(p);
	}
}
int KernelSem::deblock(int n){

	this->val+=n;

	if(blockList.duzinaProlaz()<n){
		n=blockList.duzinaProlaz();
	}

	for(int i=0; i<n;i++){
		PCB* p=blockList.izbaciPrvi();
		sleepLista.izbaci(p);
		p->blokiran=0;
		Scheduler::put(p);
	}

	return n;

}

int KernelSem::getVal() const{
	return this->val;
}

void KernelSem::setVal(int i){
	val=i;
}


