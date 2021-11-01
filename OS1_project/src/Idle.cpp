#include "Idle.h"

static volatile int idleku=0;
Idle :: Idle() {}


void Idle::run(){
	while(idleku==0){
		idleku/=2;
	}
}

