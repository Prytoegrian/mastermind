#include <string>

using namespace std;

class Status {
public:
    Status(string solutionToBreak, string currentTry); //, Rules pour les cas d'erreur

    bool isFail();

    bool isError();

    bool isSuccess();

private:
    bool hasError(string solutionToBreak, string currentTry);
    bool hasRepetition(string currentTry);
    bool hasForbiddenChars(string solutionToBreak, string currentTry);
    bool isCharInString(char needle, string haystack);
    const int SUCCESS = 0;
    const int FAIL = 1;
    const int ERROR = 2;
    int state;
};
