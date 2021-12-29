#include <cmath>
#include <iostream>
using namespace std;

int main() {
    double s, a;
    string mode;
    while(cin >> s >> a >> mode) {
        if (mode.at(0) == 'm')
            a /= 60;
        a = fmod(a, 360);
        if (a > 180)
            a = 360 - a;
        printf("%.6lf %.6lf\n",
               2 * acos(-1) * (s + 6440) * (a / 360),
               2 * (s + 6440) * sin(a * acos(-1) / 360));
    }
    return 0;
}