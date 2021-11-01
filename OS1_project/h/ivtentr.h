#ifndef SEM_IVTENTR_H_
#define SEM_IVTENTR_H_

#include "event.h"

class KernelEv;

typedef void interrupt (*pInterrupt)(...);

#define PREPAREENTRY(broj, fleg)\
	void interrupt prekid##broj(...);\
	IVTEntry entry##broj(broj,prekid##broj);\
	void interrupt prekid##broj(...){\
	entry##broj.signal();\
	if (fleg) entry##broj.pozovi();\
	}


class IVTEntry{
public:
	IVTEntry(IVTNo ivtno, pInterrupt p);
	~IVTEntry();

	void pozovi();

	void signal();

	void setMyEvent(KernelEv* k);

	static IVTEntry* getEntry(IVTNo i);

private:
	pInterrupt staraRutina;
	IVTNo bru;
	KernelEv* myEvent;
};




#endif /* SEM_IVTENTR_H_ */
