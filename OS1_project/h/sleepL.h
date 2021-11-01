#ifndef STRUKT_SLEEPL_H_
#define STRUKT_SLEEPL_H_
#include "PCB.h"
//#include "iostream.h"
class KernelSem;

class SleepLista {
	struct Elem {
		PCB* p;
		KernelSem * s;
		int time;
		Elem* next;
		Elem(PCB* pcb, int t, KernelSem *ss) {
			p = pcb;
			s=ss;
			time = t;
			next = 0;
		}
	};
	Elem* prvi;
	int num_of_proccesses;


public:
	SleepLista() {
		prvi = 0;
		num_of_proccesses = 0;
	}

	void dodaj(PCB* pcb, int x, KernelSem * s) {

		int cnt;

		Elem *tek, *prev;

		if (!prvi) {
			prvi = new Elem(pcb, x, s);
			num_of_proccesses++;
			return;
		}

		tek = prvi;
		prev = 0;
		cnt = prvi->time;

		while (x >= cnt && tek != 0) {
			prev = tek;
			tek = tek->next;
			if (tek)
			cnt += tek->time;
		}

		if (!prev) {
			prvi = new Elem(pcb, x, s);
			prvi->next = tek;
			tek->time = tek->time - prvi->time;
		}

		else {

			int oldcnt = cnt;
			if (tek) {
				oldcnt = cnt - tek->time;
			}
			Elem *novi = new Elem(pcb, x - oldcnt, s);
			prev->next = novi;
			novi->next = tek;
			if (tek) {
				tek->time = tek->time - novi->time;
			}
		}

		num_of_proccesses++;

	}

		void izbaci(PCB * pcb){

			Elem* tek=prvi;
			Elem* pret=0;

			while(tek){
				if(tek->p!=pcb){
				pret=tek;
				tek=tek->next;
			} else {
				Elem* old=tek;
				tek=tek->next;
				if(tek)
					if(old->time)
						tek->time+=old->time;
				if(!pret) prvi=tek;
				 else pret->next=tek;
				delete old;
				num_of_proccesses--;
			  }
			}


		}

	/*	int velicina() const {
			return num_of_proccesses;
		}
*/
		void azuriraj(){
			prvi->time--;
			// cout<<"Smanjen:"<<prvi->time<<endl;
			while (prvi && prvi->time==0) {
				//cout<<"izbacen iz liste"<<endl;
				prvi->p->istekloVreme=1;
				prvi->s->blockList.izbaciPCB(prvi->p);
				prvi->s->setVal(prvi->s->getVal()+1);
				prvi->p->blokiran=0;
				if(!prvi->p->zavrsio)
					Scheduler::put(prvi->p);
				Elem *stari=prvi;
				prvi=prvi->next;
				num_of_proccesses--;
				delete stari;
			}
		}

		int prazna(){
			if(prvi) return 0;
			else return 1;
		}

		~SleepLista(){
			while(prvi){
				Elem* stari=prvi;
				prvi=prvi->next;
				delete stari;
			}
			prvi=0;
		}


};
#endif /* STRUKT_SLEEPL_H_ */
