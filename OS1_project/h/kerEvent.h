#ifndef SEM_KEREVENT_H_
#define SEM_KEREVENT_H_

#include "event.h"
class PCB;

class KernelEv{
public:

	KernelEv(IVTNo ivtno);
	~KernelEv();
	void wait();
	void signal();

	PCB* owner;
private:
	char val;
	char blk;
};



#endif /* SEM_KEREVENT_H_ */
