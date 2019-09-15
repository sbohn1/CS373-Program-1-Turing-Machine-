/***************************************/
/*Driver Class: Runs the turing machine*/
/*Reqires Classes.h and Structs.h      */
/*Coded By Steven Bohn                 */
/***************************************/

//Librarys
#include <iostream>
#include <string>
#include <fstream>

//Self-made classes/structures
#include "Classes.h"
#include "Structs.h"

using namespace std;

int main(int argc, char* argv[]) {

	//Input Stream
	ifstream fin;

	//Initialize the turing machine and input data from input file
	TuringMachine tm(argv[2], atoi(argv[3]));
	tm.parseData(fin, argv[1]);

	Tape tape = tm.getTape();

	//Run the turing machine, which will output its step and its exit state
	exitState  exit = tm.runMachine();

	return 0;
}
