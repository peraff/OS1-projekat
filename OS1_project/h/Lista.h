#ifndef LISTA_H_
#define LISTA_H_

class PCB;

class Lista{
	struct Elem{
		PCB* p;
		Elem* next;
		Elem(PCB* pcb){
			p=pcb;
			next=0;
		}
	};
	Elem* prvi,*posl;
	int num_of_proccesses;

public:
	Lista(){
		prvi=posl=0;
		num_of_proccesses=0;
	}
	void dodaj(PCB* pcb){
		posl=(!prvi?prvi:posl->next)=new Elem(pcb);
		//Elem* novi=new Elem(pcb);
		//novi->next=prvi;
		//prvi=novi;
		num_of_proccesses++;
	}

	/* int duzina()const {
		return num_of_proccesses;
	}*/

	int duzinaProlaz(){
		int n=0;
		Elem *tek=prvi;
		while(tek){
			n++;
			tek=tek->next;
		}
		return n;
	}

	void izbaciPCB(PCB* pcb){

		Elem* tek=prvi;
		Elem* pret=0;

		while(tek){
			if(tek->p!=pcb){
			pret=tek;
			tek=tek->next;
			} else {
			Elem* old=tek;
			tek=tek->next;
			if(!pret) prvi=tek;
			 else pret->next=tek;
			if(old==posl) posl=tek;
			num_of_proccesses--;
			delete old;
		  }
		}
	}

	PCB* izbaciPrvi(){
		if(prvi){
		PCB* tek=prvi->p;
		Elem* pom=prvi;
		prvi=prvi->next;
		if(!prvi) posl=0;
		num_of_proccesses--;
		delete pom;
		return tek;
		}
		else return 0;
	}


	~Lista(){
		while(prvi){
			Elem *stari=prvi;
			prvi=prvi->next;
			delete stari;
		}
		prvi=posl=0;
		num_of_proccesses=0;
	}

	int prazna(){
		if(prvi) return 0;
		else return 1;
	}

};



#endif /* LISTA_H_ */
