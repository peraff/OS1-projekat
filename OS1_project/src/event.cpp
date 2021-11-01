#include "event.h"
#include "kerEvent.h"


Event::Event(IVTNo ivtno){
	myImpl=new KernelEv(ivtno);
}

Event::~Event(){
	delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
