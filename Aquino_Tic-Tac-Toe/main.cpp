#include <iostream>
#include <string>
using namespace std;

string valids[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
char grid[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

string spacer(int count) {
	string space = "";
	while (count--) space += " ";
	return space;
}

void display() {
	int space = 50;
	cout << "\n\n\n"
		 << spacer(space) << " " << grid[0] << " | " << grid[1] << " | " << grid[2] << endl
		 << spacer(space) << "-----------" << endl
		 << spacer(space) << " " << grid[3] << " | " << grid[4] << " | " << grid[5] << endl
		 << spacer(space) << "-----------" << endl
		 << spacer(space) << " " << grid[6] << " | " << grid[7] << " | " << grid[8] << "\n\n\n\n";
}

string turnInput(bool invalid, bool taken, bool first) {
	int space = 40;
	cout << spacer(space) << "Player " << (first ? "1 [O]\n" : "2 [X]\n");
	if (invalid) cout << spacer(space) << "Invalid input!\n";
	if (taken) cout << spacer(space) << "Input is already taken!\n";
	cout << spacer(space) << "Please input a valid number: ";
	string input;
	getline(cin, input);
	return input;
}

bool isInvalid(string input) {
	for (int i = 0; i < 9; i++) if (input == valids[i]) return false;
	return true;
}

bool isTaken(int input) {
	if (grid[input - 1] == 'X' || grid[input - 1] == 'O') return true;
	return false;
}

void turnProcess(int turn, bool first) {
	grid[turn - 1] = first ? 'O' : 'X';
}

bool hasWinner(bool first) {
	bool end = false;
	if ((grid[0] == grid[1] && grid[0] == grid[2]) ||
	    (grid[3] == grid[4] && grid[3] == grid[5]) ||
	    (grid[6] == grid[7] && grid[6] == grid[8]) ||
	    (grid[0] == grid[3] && grid[0] == grid[6]) ||
	    (grid[1] == grid[4] && grid[1] == grid[7]) ||
	    (grid[2] == grid[5] && grid[2] == grid[8]) ||
	    (grid[0] == grid[4] && grid[0] == grid[8]) ||
	    (grid[2] == grid[4] && grid[2] == grid[6])) end = true;
	if (end) {
		system("cls");
		display();
		cout << spacer(40) << "Player " << (first ? "1" : "2") << " wins!!!!\n\n\n";
	}
	return end;
}

void draw() {
	system("cls");
		display();
		cout << spacer(40) << "Game Draw!!!!\n\n\n";
}

void tictactoe() {
	string input;
	bool invalid = false,
		 taken = false,
		 first = false;
	
	int turn = 0;
	while (!hasWinner(first)) {
		turn++;
		if (turn == 10) {
			draw();
			break;
		}
		
		first = first ? false : true;
		while (true) {
			system("cls");
			display();
			input = turnInput(invalid, taken, first);
			invalid = isInvalid(input);
			taken = false;
			if (invalid) continue;
			taken = isTaken(stoi(input));
			if (!taken) break;
		}
		
		turnProcess(stoi(input), first);
	}
	;
}

int main() {
	tictactoe();
	
	return 0;
}
