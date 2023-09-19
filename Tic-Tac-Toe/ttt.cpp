#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <vector>
#include <sstream>

void grid(int x);
void changeArray(char arr[], int size);
int getRandomNumber(int minRange, int maxRange);
int checkWin();
int checkIntInput();
int playerTurn(int x);
void singleP(int m);
void twoP();
int getRandomNumberFromList(std::string s);
int impossible(bool b);

char t[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
std::vector<int> tt;

int main() {
    std::cout << "\n\nTIC-TAC-TOE\n\n";

    std::cout << "Type 1 for single-player mode, versus computer.\n"
              << "Type 2 for two-player mode.\n\n";
    int p = checkIntInput();
    
    int m = p;
//    int m = 0;
//    if (p == 1) {
//        std::cout << "\nType 1 for random mode.\n"
//                  << "Type 2 for impossible mode.\n\n";
//        m = checkIntInput();
//    }
    
    grid(99);
    std::cout << "Type in the corresponding number in the grid to play:\n\n";
    changeArray(t, 9);
    
    srand(time(0));
    if (p == 1) singleP(m);
    else twoP();

    std::string a;
    std::getline(std::cin, a);

    return 0;
}

void grid(int x) {
    x--;
    if (x < 9) { //player turn
        t[x] = 'x';
    }
    else if (x < 18) {
        t[x - 9] = 'o';
    }
    //else std::cout << "Error";

    std::cout << "\n" <<
                 " " << t[0] << " | " << t[1] << " | " << t[2] << "\n - - - - - \n " 
                     << t[3] << " | " << t[4] << " | " << t[5] << "\n - - - - - \n " 
                     << t[6] << " | " << t[7] << " | " << t[8] << "\n\n";
}

void changeArray(char arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = ' ';
    }
}

int getRandomNumber(int minRange, int maxRange) {
    return minRange + rand() % (maxRange - minRange + 1);
}

int checkWin() {
    bool x = 0;
    if ((t[0] == t[1]) && (t[1] == t[2]) && (t[0] != ' ')) x = 1;
    if ((t[3] == t[4]) && (t[4] == t[5]) && (t[3] != ' ')) x = 1;
    if ((t[6] == t[7]) && (t[7] == t[8]) && (t[6] != ' ')) x = 1;
    if ((t[0] == t[3]) && (t[3] == t[6]) && (t[0] != ' ')) x = 1;
    if ((t[1] == t[4]) && (t[4] == t[7]) && (t[1] != ' ')) x = 1;
    if ((t[2] == t[5]) && (t[5] == t[8]) && (t[2] != ' ')) x = 1;
    if ((t[0] == t[4]) && (t[4] == t[8]) && (t[0] != ' ')) x = 1;
    if ((t[2] == t[4]) && (t[4] == t[6]) && (t[2] != ' ')) x = 1;

    return x;
}

int checkIntInput() {
    int x;
    while (true) {
        std::cin >> x;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Not an integer." << std::endl;
            std::cin.clear();  // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        }
        else if ((x > 2) || (x < 1)) std::cout << "Invalid input. Out of bounds." << std::endl;
        else break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return x;
}

int playerTurn() {
    int x;
    
    while (true) {
        std::cin >> x;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Not an integer." << std::endl;
            std::cin.clear();  // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        }
        else if ((x > 9) || (x < 1)) std::cout << "Invalid input. Out of bounds." << std::endl;
        else if (t[x - 1] != ' ') std::cout << "Invalid input. Cell occupied." << std::endl;
        else break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    tt.push_back(x);
    return x;
}

void singleP(int m) {
    int x;
    bool a = 0;//getRandomNumber(0, 1);

    for (int i = 0; i < 5; i++) {
        if (!(a && i == 0)) {
            std::cout << "Your Turn: ";
            grid(playerTurn());
            
            if (checkWin()) {
                std::cout << "You Win!\n\n";
                break;
            }
            else if (i == 4 && !a) {
                std::cout << "Draw!\n\n";
                break;
            }
        }

        if (m == 1) do x = getRandomNumber(1, 9); while (t[x - 1] != ' ');
        else x = impossible(a);
        std::cout << "Computer's Turn: " << x << '\n';
        grid(x + 9);

        if (checkWin()) {
            std::cout << "You Lose!";
            break;
        }
        else if (i == 4) {
            std::cout << "Draw!\n\n";
            break;
        }
    }
}

int impossible(bool b) {
    int x = tt[tt.size() - 1];

    switch (x) {
        case 1:
            x = getRandomNumberFromList("3 5 7 9"); break;
        default: std::cout << "ERROR";
    }
    
    return x;
}

int getRandomNumberFromList(std::string s) {
    std::istringstream iss(s);
    std::vector<int> arr;

    //std::cout << s;
    int num, c = 0;
    while (iss >> num) {
        arr.push_back(num);
        c++;
        //std::cout << c;
    }

    return arr[getRandomNumber(0, c - 1)];
}

void twoP() {
    int x;

    for (int i = 0; i < 5; i++) {
        std::cout << "Player 1's Turn: ";
        grid(playerTurn());

        if (checkWin()) {
            std::cout << "Player 1 Wins!\n\n";
            break;
        }
        else if (i == 4) {
            std::cout << "Draw!\n\n";
            break;
        }

        std::cout << "Player 2's Turn: ";
        grid(playerTurn() + 9);

        if (checkWin()) {
            std::cout << "Player 2 Wins!\n\n";
            break;
        }
    }
}
