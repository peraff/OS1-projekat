#include "kerEvent.h"
#include "PCB.h"
#include "ivtentr.h"
#include "kersem.h"
#include "sleepL.h"

KernelEv::KernelEv(IVTNo ivtno){
	asm cli
	owner=(PCB*)running;
	blk=0;
	val=0; //stavi na 0
	IVTEntry::getEntry(ivtno)->setMyEvent(this);
	asm sti
}


KernelEv::~KernelEv(){
	if(owner)
	if(owner->blokiran && !owner->zavrsio){
		owner->blokiran=0;
		Scheduler::put(owner);
	}
}
void KernelEv::wait(){

	//cout<<"pozvan wait"<<endl;
	asm cli

	if(running != owner) {
		asm sti
		return;
	}
	if(val)
		val=0;
	else{
		blk=1;
		owner->blokiran=1;
		dispatch();
	}
	asm sti

}
void KernelEv::signal(){

	if(!val){
		if(blk){
			owner->blokiran=0;
			blk=0;
			Scheduler::put(owner);
		} else val=1;
	}// else val=1;
}
