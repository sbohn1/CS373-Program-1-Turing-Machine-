/***************************************/
/*Structs.h: contains Structures & enum*/
/*used in the Turing machine class*/
/***************************************/

#ifndef STRUCTS_SB
#define STRUCTS_SB

//Exit states enum, declares outcome of
//the "runMachine" function
enum exitState {
	accept, reject, quit
};

//State structure: the structure for each
//state within the turing machine. Special
//Flags for all special cases
struct State {
	int number = -1;
	bool startFlag = false;
	bool acceptFlag = false; 
	bool rejectFlag = false;
};

//Transition structure: holds each value
//in a transition statement (q,a,r,b,x)
struct Transition {
	int checkState = 0;
	int changeState = 0;
	char checkValue = ' ';
	char changeValue = ' ';
	char direction = ' ';
};

#endif // !STRUCTS_SB

