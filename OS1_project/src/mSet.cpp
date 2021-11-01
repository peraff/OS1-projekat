/*
 * mainSet.cpp
 *
 *  Created on: Aug 15, 2019
 *      Author: OS1
 */

#include "mainSet.h"

unsigned oldTimerOFF, oldTimerSEG; // stara prekidna rutina

Idle* idle;
PCB* idlePCB;

void inic(){
	asm{
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEG	 //	postavlja staru rutinu
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

// vraca staru prekidnu rutinu
void restore(){
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax

		pop es
		sti
	}
}

void MainSet::mainSet(){
	inic();

	idle=new Idle();                 //inic idol nitii njeno stanje nikad nije zavrseno, ispitujes u timer pre ubacivanja u Scheduller, IDle ID=0;
	idle->myPCB->zavrsio=-1;
	idle->myPCB->kvant=1;
	idlePCB=idle->myPCB;

	Thread* temp=new Thread();			//pravljenje pcba za main funkciju. Main ID=1
	delete temp->myPCB->mojStek;
	running=(volatile PCB*)temp->myPCB;


}

void MainSet::mainReset(){
	restore();
}


