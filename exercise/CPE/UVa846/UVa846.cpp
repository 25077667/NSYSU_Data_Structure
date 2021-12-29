#include <iostream>
using namespace std;

int main() {
    int n, x, y, step;
    cin >> n;
    while (n--) {
        cin >> x >> y;

        int distance = y - x;
        if (distance < 4)
            cout << distance << endl;
        else if (distance < 0)
            continue;
        else {
            for (step = 2; distance > 0; step += 2) {
                if (distance - step < 0)
                    break;
                else
                    distance -= step;
            }
            if (!distance)
                cout << step - 2 << endl;
            else if (step / 2 >= distance)
                cout << step - 1 << endl;
            else
                cout << step << endl;
        }
    }
    return 0;
}