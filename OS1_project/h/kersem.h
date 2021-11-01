#ifndef SEM_KERSEM_H_
#define SEM_KERSEM_H_

#include "Lista.h"
#include "semaphor.h"

class SleepLista;

extern SleepLista sleepLista;

class KernelSem{

public:
	~KernelSem();
	int getVal() const;
	void setVal(int);

	int wait(Time maxTimeToWait);
	int signal(int n=0);

	Lista blockList;

protected:

	void block(int);
	void deblock();
	int deblock(int);

private:
	int val;


};


#endif /* SEM_KERSEM_H_ */
