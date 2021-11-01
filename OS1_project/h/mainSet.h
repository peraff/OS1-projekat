/*
 * mainSet.h
 *
 *  Created on: Aug 15, 2019
 *      Author: OS1
 */

#ifndef MAINSET_H_
#define MAINSET_H_

#include "PCB.h"
#include "Idle.h"


extern PCB* idlePCB;

// postavlja novu prekidnu rutinu
void inic();

// vraca staru prekidnu rutinu
void restore();

class MainSet{
public:
	friend class Thread;
	friend class PCB;
	static void mainSet();
	static void mainReset();
};


#endif /* MAINSET_H_ */
