#include <iostream>
using namespace std;

int main() {
    int num, cases = 0;
    while (cin >> num && num > 0) {
        int answer = 0;
        for (; num; num >>= 1)
            answer++;
        printf("Case %d: %d\n", ++cases, answer);
    }
    return 0;
}