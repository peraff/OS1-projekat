
#ifndef STRUKT_NIZ_H_
#define STRUKT_NIZ_H_

class PCB;

class Niz{
public:

	Niz(){
		niz=new PCB*[kap=10];
		n=0;
	}

	void volatile dodaj(PCB* pcb, int id) volatile {
		int i=0;
		if(n==kap){
			PCB** pom=new PCB*[kap+=10];
			for(; i<n;i++) pom[i]=niz[i];
			delete niz;
			niz=pom;
		}
		/*i=0;
		for(; i<n;i++){
			if (niz[i]==pcb) return;
		}*/

		niz[id]=pcb;
		n++;
	}

	 PCB* dohvInd(ID i) volatile {
		if (niz[i]!=0 && n>0) return niz[i];
		return 0;
	}


	volatile PCB* uzmiPCB(int i){
		if(niz[i]!=0 && n>0) {
			PCB* tmp=niz[i];
			niz[i]=0;
			n--;
			return tmp;
		}
		return 0;
	}

	~Niz(){
		delete [] niz;
	}
private:
	PCB** niz;
	int kap;
	int n;
};




#endif /* STRUKT_NIZ_H_ */
