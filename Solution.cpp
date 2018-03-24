#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include "Solution.h"

using namespace std;

Solution::Solution(string authorizedChars) {
    string a = authorizedChars;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(a.begin(), a.end(), default_random_engine(seed));

    toBreak = a;
}

string Solution::getToBreak() {
    return toBreak;
}

int Solution::getToBreakLength() {
    return toBreak.length();
}

bool Solution::isFound(string attempt) {
    return attempt == toBreak;
}

string Solution::getDistance(string attempt) {
    string distance = "";
    for (size_t i = 0; i < attempt.length(); ++i) {
        if (attempt[i] == toBreak[i]) {
            distance += "+";
        } else {
            distance += "-";
        }
    }
    return distance;
}
