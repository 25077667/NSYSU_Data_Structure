#include <iostream>
#include <stack>
using namespace std;

int main() {
    string input;
    while (cin >> input) {
        stack<char> s;
        bool isValid = true;
        for (auto i : input) {
            if (i == '(' || i == '[' || i == '{')
                s.push(i);
            else if (i == ')') {
                if (s.top() == '(')
                    s.pop();
                else {
                    isValid = false;
                    break;
                }
            } else if (i == ']') {
                if (s.top() == '[')
                    s.pop();
                else {
                    isValid = false;
                    break;
                }
            } else if (i == '}') {
                if (s.top() == '{')
                    s.pop();
                else {
                    isValid = false;
                    break;
                }
            } else
                continue;
        }
        if (isValid)
            cout << "Accept!" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}