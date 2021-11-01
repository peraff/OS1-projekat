/*
 * thread.cpp
 *
 *  Created on: Aug 11, 2019
 *      Author: OS1
 */

#include "PCB.h"

Thread::Thread (StackSize stackSize, Time timeSlice){
	myPCB=new PCB(this, stackSize, timeSlice);
}


void Thread::start(){
	myPCB->start();
}

Thread::~Thread(){
	waitToComplete();
	delete myPCB;
	myPCB=0;
}

ID Thread::getId(){
	return myPCB->id;
}

ID Thread::getRunningId(){
	return running->id;
}

Thread * Thread::getThreadById(ID id){
 return (nizPCB.dohvInd(id)->mojaNit);
}


void Thread::waitToComplete(){
	if(this->myPCB->zavrsio || this->myPCB==running){
		return;
	}
	running->blokiran=1;
	this->myPCB->listaBlokiranih.dodaj((PCB*)running);
	dispatch();
}

