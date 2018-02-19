#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

const unsigned int LOOP = 10;

const int NUMBER_EQUAL = 0;
const int FIRST_LESS = -1;
const int FIRST_GREATER = 1;

const string AUTHORIZED_CHAR = "RYBOP";

/*
 * TODO :
 * - improve error handling
 * - level system, w/o position indication, number of tries
 * - repetition forbidden
 */

/**
 * Compare two integers
 *
 * @param int a
 * @param int b
 *
 * @return -1 if a < b, 1 if a  > b, 0 otherwise
 */
int compare(int a, int b);

/**
 * Get a randomized string to play with
 *
 * @param string authorizedChar String of letters possibilities
 *
 * @return string
 */
string stringToGuess(string authorizedChar);

/**
 * in_array in c
 */
bool isCharInString(char needle, string haystack);

/**
 * Checks if attempt repeats a letter
 *
 * @param string attempt String of the attempt N
 */
bool hasRepetition(string attempt);

/**
 * Returns if the mastermind's distance shows error
 */
bool hasError(string patternMatching);

/**
 * Returns the mastermind's distance between the solution and the sequence to guess
 *
 * @param string attempt String of the attempt N
 * @param string toBreak Solution
 */
string getPatternMatching(string attempt, string toBreak);

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

// Compare two integers
int compare(int a, int b) {
    if (a == b) {
        return NUMBER_EQUAL;
    } else if (a < b) {
        return FIRST_LESS;
    }

    return FIRST_GREATER;
}

// Get a randomized string to play with
string stringToGuess(string authorizedChar) {
    string toBreak = authorizedChar;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(toBreak.begin(), toBreak.end(), default_random_engine(seed));

    return toBreak;
}

// in_array in c
bool isCharInString(char needle, string haystack) {
    for (size_t i = 0; i < haystack.length(); ++i) {
        if (needle == haystack[i]) {
            return true;
        }
    }

    return false;
}

// Checks if attempt repeats a letter
bool hasRepetition(string attempt) {
    for (size_t i = 0; i < attempt.length(); i++) {
        // Loop invariant :
        // for all attempt[i], attempt[x] is already verified (for all x < i) !
        if (isCharInString(attempt[i], attempt.substr(i+1))) {
            return true;
        }
    }

    return false;
}

// Returns if the mastermind's distance shows error
bool hasError(string patternMatching) {
    for (size_t i = 0; i < patternMatching.length(); ++i) {
        if (isCharInString('-', patternMatching) || isCharInString('x', patternMatching)) {
            return true;
        }
    }
    return false;
}

// Returns the mastermind's distance between the solution and the sequence to guess
string getPatternMatching(string attempt, string toBreak) {
    string patternMatching = "";
    for (size_t i = 0; i < attempt.length(); ++i) {
        if (!isCharInString(attempt[i], toBreak)) {
            patternMatching += "x";
        } else if (attempt[i] == toBreak[i]) {
            patternMatching += "+";
        } else {
            patternMatching += "-";
        }
    }

    return patternMatching;
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
    unsigned int tries = 0;
    string attempt;
    string toBreak = stringToGuess(AUTHORIZED_CHAR);
    unsigned int toBreakLength = toBreak.length();
    bool found = false;
    do {
        ++tries;
        cout << ">> Try to break sequence (" << tries << "/" << LOOP << ") : " << endl;
        cin >> attempt;
        switch (compare(attempt.length(), toBreakLength)) {
            case FIRST_LESS:
                cout << ">> Guessing is too short" << endl;
                continue;
            case FIRST_GREATER:
                cout << ">> Guessing is too long" << endl;
                continue;
        }
        if (hasRepetition(attempt)) {
            cout << ">> Guessing has repetition" << endl;
        }
        string patternMatching = getPatternMatching(attempt, toBreak);
        if (!hasError(patternMatching)) {
            found = true;
            break;
        }

        cout << ">> Result : " << patternMatching << endl;
    } while(tries < LOOP);

    if (found) {
        cout << ">> Congrats ! Solution " << toBreak << " was found in " << tries << " tries." << endl;
    } else {
        cout << ">> Sorry, solution " << toBreak << " wasn't found." << endl;
    }
}
