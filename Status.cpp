#include <string>
#include "Status.h"

using namespace std;

Status::Status(string solutionToBreak, string currentTry) {
    if (hasError(solutionToBreak, currentTry)) {
        state = ERROR;
    } else if (solutionToBreak != currentTry) {
        state = FAIL;
    } else {
        state = SUCCESS;
    }
}

bool Status::isFail() {
    return state == FAIL;
}

bool Status::isError() {
    return state == ERROR;
}

bool Status::isSuccess() {
    return state == SUCCESS;
}

bool Status::hasError(string solutionToBreak, string currentTry) {
    if (solutionToBreak.length() != currentTry.length()) {
        return true;
    }
    if (hasRepetition(currentTry)) {
        return true;
    }
    if (hasForbiddenChars(solutionToBreak, currentTry)) {
        return true;
    }
    return false;
}

// Checks if currentTry repeats a letter
bool Status::hasRepetition(string currentTry) {
    for (size_t i = 0; i < currentTry.length(); i++) {
        // Loop invariant :
        // for all currentTry[i], currentTry[x] is already verified (for all x < i) !
        if (isCharInString(currentTry[i], currentTry.substr(i+1))) {
            return true;
        }
    }

    return false;
}

bool Status::hasForbiddenChars(string solutionToBreak, string currentTry) {
    for (size_t i = 0; i < currentTry.length(); i++) {
        if (!isCharInString(currentTry[i], solutionToBreak)) {
            return true;
        }
    }

    return false;
}

// in_array in c
bool Status::isCharInString(char needle, string haystack) {
    for (size_t i = 0; i < haystack.length(); ++i) {
        if (needle == haystack[i]) {
            return true;
        }
    }

    return false;
}
