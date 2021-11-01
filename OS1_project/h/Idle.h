#ifndef IDLE_H_
#define IDLE_H_

#include "PCB.h"

class Idle : public Thread {
public:
	friend class PCB;
	Idle();
	void run();
};



#endif /* IDLE_H_ */
