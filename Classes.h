/***************************************/
/*Classes.h: Holds all classes in proj1*/
/*Holds Tape and Turing Machine classes*/
/*Requires Structs.h                   */
/***************************************/

#ifndef CLASSES_SB
#define CLASSES_SB

//Referenced Headers
#include "Structs.h"

//Referenced Librarys
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//Tape class, holds all input values
class Tape {
private:
	std::vector<char> tape;
	int position = 0;
public:
	Tape() { ; };
	Tape(std::string);
	void fill(std::string);
	void Move(char);
	void overWrite(int, char);
	std::vector<char> getTape() { return tape; };
	int getPos() { return position; };
};

//Turing Machine Class: Acts as a simple Turing Machine using an input file (argv[1]),
//A tape value (arg[2]) and a limit of moves (arg[3])
class TuringMachine {
private:
	State states[1001];
	std::vector<Transition> instructions;
	Tape tape;
	int turns;
public:
	TuringMachine(std::string, int);
	void parseData(std::ifstream&, std::string);
	exitState runMachine(void);
	Tape getTape() { return tape; };
	std::vector<Transition> getInstr() { return instructions; };
	int findStartState();
	std::vector<int> findAcceptStates();
	std::vector<int> findRejectStates();
};

#endif // !CLASSES_SB
