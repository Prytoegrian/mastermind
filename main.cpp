#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

#define LOOP 10

#define TO_GUESS "RYBOP"

const char AUTHORIZED_CHAR[] = "RYBOP";

/**
 * in_array in c
 */
bool isCharInString(char needle, string haystack) {
    for (size_t i = 0; i < haystack.length(); ++i) {
        if (needle == haystack[i]) {
            return true;
        }
    }

    return false;
}

/**
 * Returns if the mastermind's distance shows error
 */
bool hasError(string patternMatching) {
    for (size_t i = 0; i < patternMatching.length(); ++i) {
        char minus = '-';
        char x = 'X';
        if (isCharInString(minus, patternMatching) || isCharInString(x, patternMatching)) {
            return true;
        }
    }
    return false;
}

/**
 * Returns the mastermind's distance between the solution and the sequence to guess
 *
 * @var string guessing
 */
string getPatternMatching(string guessing) {
    string patternMatching = "";
    for (size_t i = 0; i < guessing.length(); ++i) {
        if (!isCharInString(guessing[i], TO_GUESS)) {
            patternMatching += "X";
        } else if (guessing[i] == TO_GUESS[i]) {
            patternMatching += "+";
        } else {
            patternMatching += "-";
        }
    }

    return patternMatching;
}

int main(int const argc, char const *argv[]) {
    cout << " ---- Mastermind ---- " << endl;
    cout << " -------------------- " << endl;
    cout << "Available colors : R(ed) Y(ellow) B(lue) O(range) P(ink)" << endl;
    cout << "Response := + : color in good position | - : color in wrong position | x : bad color" << endl;

    int attempt = 0;
    string guessing;
    bool found = false;
    do {
        ++attempt;
        cout << "Try to guess sequence : " << endl;
        cin >> guessing;
        if (guessing.length() != strlen(TO_GUESS)) {
            cout << "Guessing is too short or too long" << endl;
            continue;
        }
        string patternMatching = getPatternMatching(guessing);
        if (!hasError(patternMatching)) {

            found = true;
            break;
        }

        cout << "Result : " << patternMatching << endl;
    } while(attempt < LOOP);

    if (found) {
        cout << "Congrats ! Solution " << TO_GUESS << " was found in " << attempt++ << " try." << endl;
    } else {
        cout << "Sorry, solution " << TO_GUESS << " wasn't found." << endl;
    }

    return 0;
}
