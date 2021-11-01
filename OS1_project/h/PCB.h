/*
 * PCB.h
 *
 *  Created on: Aug 10, 2019
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include <SCHEDULE.h>
#include <dos.h>

#include "thread.h"
#include "niz.h"
#include "Lista.h"

extern volatile Niz nizPCB;
extern volatile PCB* running;


void interrupt timer();

void tick();

class PCB{

public:

	PCB(Thread* myThread, StackSize stackSize, Time timeSlice);

	virtual ~PCB();			//vidi sto ti je ovde virtual destruktor ako se ne poziva nikad iz izvedene klase
	void start();

	unsigned sp;
	unsigned ss;
	unsigned bp;

	//flegovi
	int zavrsio;
	int kvant;
	int pokrenut;
	int blokiran;
	int istekloVreme;  //koristi se kod wait(timme) ako je isteklo dodato vreme.

	StackSize mojaVelicina;
	unsigned* mojStek;

	Thread* mojaNit;

	Lista listaBlokiranih;

	static void wrapper(Thread* mojaNit);
	int id;

private:
	friend class MainSet;
	friend class Thread;
	static int posID;
};

#endif /* PCB_H_ */
