#include "mainSet.h"

extern int userMain (int argc, char* argv[]);

int main(int argc, char* argv[]){

	MainSet::mainSet();
	//syncPrintf("User main starts\n");

	int ret=userMain(argc, argv);

	//syncPrintf("User main ends\n");
	MainSet::mainReset();

	return ret;

}



