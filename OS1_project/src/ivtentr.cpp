#include "ivtentr.h"
#include "kerEvent.h"
#include <dos.h>
#include "iostream.h"

IVTEntry* nizEntrija[256];

IVTEntry::IVTEntry(IVTNo ivtno, pInterrupt p){
	asm cli
	bru=ivtno;
	staraRutina=getvect(ivtno);
	setvect(ivtno, p);
	myEvent=0;
	nizEntrija[ivtno]=this;
	asm sti
}

IVTEntry::~IVTEntry(){
	asm cli
	setvect(bru, staraRutina);
	asm sti
}

void IVTEntry::pozovi(){
	staraRutina();
}

void IVTEntry::signal(){
	if(myEvent)
		myEvent->signal();
}

void IVTEntry::setMyEvent(KernelEv * k){
	myEvent=k;
}

IVTEntry* IVTEntry:: getEntry(IVTNo i){
	return nizEntrija[i];
}

