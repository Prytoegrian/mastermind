#include <iostream>
#include <cstring>
#include <string>
#include "Solution.h"
#include "Status.h"

using namespace std;

const unsigned int LOOP = 10;

const string AUTHORIZED_CHAR = "RYBOP";

/*
 * TODO :
 * - improve error handling
 * - level system, w/o position indication, number of tries
 * - repetition forbidden or not
 */

/**
 * Man n rules
 */
void displayHelp();

/**
 * Let's play !
 */
void play();

int main(int const argc, char const *argv[]) {
    cout << " -------------------- " << endl;
    cout << " ---- Mastermind ---- " << endl;
    cout << " -------------------- " << endl;
    if (argc > 1 && string(argv[1]) == "-h") {
        displayHelp();
    } else {
        play();
    }

    return 0;
}

void displayHelp() {
    cout << "Mastermind is a code-breaking game for two players (Thanks Wikipedia <3)." << endl;
    cout << "Your goal is to break the sequence of color chosen by the program before the tenth try." << endl;
    cout << "Five colors are availables : R(ed) - Y(ellow) - B(lue) - O(range) - P(ink)." << endl;
    cout << endl;
    cout << "For each try, the program helps you by giving you clues about the solution : " << endl;
    cout << "   :: + for each color in good position" << endl;
    cout << "   :: - for each color in wrong position" << endl;
    cout << "   :: x for a wrong color name" << endl;
    cout << endl;
    cout << "A strange game." << endl;
    cout << "The only winning move is" << endl;
    cout << "not to play." << endl;
    cout << endl;
    cout << "How about a nice game of mastermind ?" << endl;

}

void play() {
    Solution solution = Solution(AUTHORIZED_CHAR);
    unsigned int tries = 0;
    string attempt;
    bool found = false;
    do {
        ++tries;
        cout << ">> Try to break sequence (" << tries << "/" << LOOP << ") : " << endl;
        cin >> attempt;
        Status status = Status(solution.getToBreak(), attempt);
        if (status.isError()) {
            cout << ">> Error : Attempt doesn't follow rules" << endl;
            continue;
        } else if (status.isFail()) {
            cout << ">> " << solution.getDistance(attempt) << endl;
        } else {
            found = true;
            break;
        }

    } while(tries < LOOP);

    if (found) {
        cout << ">> Congrats ! Solution " << solution.getToBreak() << " was found in " << tries << " tries." << endl;
    } else {
        cout << ">> Sorry, solution " << solution.getToBreak() << " wasn't found." << endl;
    }
}
