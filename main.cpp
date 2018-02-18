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
 * - helper : rules and CLI arguments
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
 * Checks if guessing repeats a letter
 *
 * @param string guessing String of the attempt N
 */
bool hasRepetition(string guessing);

/**
 * Returns if the mastermind's distance shows error
 */
bool hasError(string patternMatching);

/**
 * Returns the mastermind's distance between the solution and the sequence to guess
 *
 * @param string guessing String of the attempt N
 * @param string toGuess Solution
 */
string getPatternMatching(string guessing, string toGuess);

int main(int const argc, char const *argv[]) {
    cout << " ---- Mastermind ---- " << endl;
    cout << " -------------------- " << endl;
    cout << "Available colors : R(ed) Y(ellow) B(lue) O(range) P(ink)" << endl;
    cout << "Response := + : color in good position | - : color in wrong position | x : bad color" << endl;

    unsigned int attempt = 0;
    string guessing;
    string toGuess = stringToGuess(AUTHORIZED_CHAR);
    unsigned int toGuessLength = toGuess.length();
    bool found = false;
    do {
        ++attempt;
        cout << ">> Try to guess sequence (" << attempt << "/" << LOOP << ") : " << endl;
        cin >> guessing;
        switch (compare(guessing.length(), toGuessLength)) {
            case FIRST_LESS:
                cout << ">> Guessing is too short" << endl;
                continue;
            case FIRST_GREATER:
                cout << ">> Guessing is too long" << endl;
                continue;
        }
        if (hasRepetition(guessing)) {
            cout << ">> Guessing has repetition" << endl;
        }
        string patternMatching = getPatternMatching(guessing, toGuess);
        if (!hasError(patternMatching)) {
            found = true;
            break;
        }

        cout << ">> Result : " << patternMatching << endl;
    } while(attempt < LOOP);

    if (found) {
        cout << ">> Congrats ! Solution " << toGuess << " was found in " << attempt << " tries." << endl;
    } else {
        cout << ">> Sorry, solution " << toGuess << " wasn't found." << endl;
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
    string toGuess = authorizedChar;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(toGuess.begin(), toGuess.end(), default_random_engine(seed));

    return toGuess;
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

// Checks if guessing repeats a letter
bool hasRepetition(string guessing) {
    for (size_t i = 0; i < guessing.length(); i++) {
        // Loop invariant :
        // for each letter guessing[i], guessing[x] when x < i is already verified !
        if (isCharInString(guessing[i], guessing.substr(i+1))) {
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
string getPatternMatching(string guessing, string toGuess) {
    string patternMatching = "";
    for (size_t i = 0; i < guessing.length(); ++i) {
        if (!isCharInString(guessing[i], toGuess)) {
            patternMatching += "x";
        } else if (guessing[i] == toGuess[i]) {
            patternMatching += "+";
        } else {
            patternMatching += "-";
        }
    }

    return patternMatching;
}
