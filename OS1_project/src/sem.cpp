#include "kersem.h"

 Semaphore::Semaphore(int init){

	 myImpl=new KernelSem();

	 myImpl->setVal(init);

 }

 int Semaphore::val() const{
	 return myImpl->getVal();
 }



 Semaphore::~Semaphore(){
	 delete myImpl;
 }

 int Semaphore:: wait (Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
 }

 int Semaphore::signal(int n){
	return myImpl->signal(n);
 }
