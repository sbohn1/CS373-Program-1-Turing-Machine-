#include "Classes.h"

using namespace std;

//Fills the tape with a read in string (arg[2])
Tape::Tape(std::string tape)
{
	//Isolate each value in the string to its own char in the tape vector
	for (int i = 0; i < tape.length(); i++) this->tape.push_back(tape.at(i));
}

//Fill function, for when empty constructor is called
void Tape::fill(std::string tape)
{
	//Isolate each value in the string to its own char in the tape vector
	for (int i = 0; i < tape.length(); i++) {
		if (tape.at(i) == '_') this->tape.push_back(' ');
		else this->tape.push_back(tape.at(i));
	}
}

//Based on the transitions, move the position integer
void Tape::Move(char dir)
{
	if (dir == 'L') position--;
	else if (dir == 'R') position++;
}

//Overwrite the value at pos with val
void Tape::overWrite(int pos, char val)
{
	if (val == '_') val = ' ';
	tape[pos] = val;
}

//Initialize the turing machines tape, numver of turns, and give every state a number
TuringMachine::TuringMachine(std::string input, int turns)
{
	tape.fill(input);
	this->turns = turns;
	for (int i = 0; i < 1001; i++) states[i].number = i;
}

//Read all data from the input file (argv[1]) fill instructions, and assign special states
void TuringMachine::parseData(std::ifstream& fin, std::string fileName)
{
	//Open the input file
	fin.open(fileName);

	std::string identifier;
	int state = -1;

	//Grab the first string
	fin >> identifier;

	//While in special states
	while (identifier == "state") {
		//Grab the state numer and its special status
		fin >> state;
		fin >> identifier;

		//Determine the appropriate flag based on identifier
		if (identifier == "accept") states[state].acceptFlag = true;
		else if (identifier == "reject") states[state].rejectFlag = true;
		else if (identifier == "start") states[state].startFlag = true;

		//Input the next lines identifier
		fin >> identifier;
	}

	int startState, nextState;
	char startChar, nextChar, direction;

	//While in transitions
	while (identifier == "transition") {
		//Input all instruction data
		fin >> startState >> startChar >> nextState >> nextChar >> direction;

		//Swap '_' with blank spaces
		if (startChar == '_') startChar = ' ';
		if (nextChar == '_') nextChar = ' ';

		//Load instruction data into a Transition struct
		Transition t;
		t.checkState = startState;
		t.checkValue = startChar;
		t.changeState = nextState;
		t.changeValue = nextChar;
		t.direction = direction;

		//Push t to the Instructions vector
		instructions.push_back(t);

		//grab next identifier
		if (fin) fin >> identifier;
		else identifier = "Done";
	}

	fin.close();
}

//Run through the Turing machine, exit with either:
//Accept, reject, or Quit
exitState TuringMachine::runMachine(void)
{
	int turn = 0;
	int instrTurn = 0;

	//Find the start state
	int start = findStartState();
	State currentState;

	int idleCount = 0;
	
	//Check if there is a start state, exit with "quit" if not
	if(start != -1) currentState = states[start];
	else {
		cout << "No start state given -> Quit" << endl;
		return quit;
	}

	cout << start;
 
	//Find the accept and reject state(s)
	vector<int> acceptStates = findAcceptStates();
	vector<int> rejectStates = findRejectStates();

	while (turn < turns) {
		//Check if in accept state, exit with "accept" if so
		for (int i = 0; i < acceptStates.size(); i++) {
			if (currentState.number == acceptStates[i]) {
				cout << " accept" << endl;
				return accept;
			}
		}

		//Check if in reject state, exit with "accept" if so
		for (int i = 0; i < rejectStates.size(); i++) {
			if (currentState.number == rejectStates[i]) {
				cout << " reject" << endl;
				return reject;
			}
		}

		//Implement instruction function
		Transition t = instructions[instrTurn];

		//Check if current state is the one referenced in the instruction
		if (currentState.number == t.checkState) {
			//Then checkv if the current value on the tape matches the referenced value
			if (tape.getTape()[tape.getPos()] == t.checkValue) {
				//Change the tapes value, position, and the current state
				tape.overWrite(tape.getPos(), t.changeValue);
				tape.Move(t.direction);
				currentState = states[t.changeState];

				//Output the new state
				cout << "->" << currentState.number;

				//Update turn counter and reset the idle counter
				turn++;
				idleCount = 0;
			}
		}
		//Otherwise, increment idle counter
		else idleCount++;

		//Determine if machine is "Stuck" Or will loop infinitely
		//If so, reject the input and end the function
		if (idleCount > instructions.size()) {
			cout << " reject: Invalid Input" << endl;
			return reject;
		}

		//Determine if all instructions have been read
		//If so, loop instructions
		instrTurn++;
		if (instrTurn == instructions.size()) instrTurn = 0;
	}

	cout << " quit" << endl;
	return quit;
}

//Find the start state
int TuringMachine::findStartState()
{
	for (int i = 0; i < 1001; i++) if (states[i].startFlag == true) return i;
	return -1;
}

//Find all accept states
std::vector<int> TuringMachine::findAcceptStates()
{
	std::vector<int> accepts;

	for (int i = 0; i < 1001; i++) if (states[i].acceptFlag == true) accepts.push_back(i);
	return accepts;
}

//Find all reject states
std::vector<int> TuringMachine::findRejectStates()
{
	std::vector<int> rejects;

	for (int i = 0; i < 1001; i++) if (states[i].rejectFlag == true) rejects.push_back(i);
	return rejects;
}