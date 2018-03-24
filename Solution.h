#include <string>

using namespace std;

class Solution {
public:
    Solution(string authorizedChars);

    string getToBreak();

    int getToBreakLength();

    bool isFound(string attempt);

    /**
     * Returns the mastermind's distance between the attempt and the solution
     * With clues : + | -
     */
    string getDistance(string attempt);

    // checking function with a error return
    // or a success return
    // in every case, an interface must be returned

private:

    /**
     * Value to play with
     */
    string toBreak;
};
