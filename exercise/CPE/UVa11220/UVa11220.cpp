#include <iostream>
#include <string>
using namespace std;

void removeConversion() {
    while (isspace(cin.peek()))
        cin.ignore();
}

bool isNullLine(string s) {
    for (auto c : s)
        if (!isspace(c))
            return false;
    return true;
}

void decode(string _line) {
    int wordCounter = 0, indexCounter = 0;
    bool hadPrint = false;
    for (auto c : _line) {
        if (isspace(c)) {
            hadPrint = false;
            indexCounter = -1;
        }

        if (!hadPrint) {
            if (wordCounter == indexCounter) {
                cout << c;
                hadPrint = true;
                indexCounter = 0;
                wordCounter++;
            } else
                indexCounter++;
        }
    }
    cout << endl;
}

int main() {
    int cases;
    cin >> cases;
    for (int i = 1; i <= cases; i++) {
        printf("Case #%d:\n", i);
        string singleLine;
        removeConversion();
        while (getline(cin, singleLine) && !isNullLine(singleLine))
            decode(singleLine);
        cout << endl;
    }

    return 0;
}