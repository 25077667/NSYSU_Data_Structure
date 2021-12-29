#include <iostream>
using namespace std;
int main() {
    int a, b, c, d;
    while (cin >> a >> b >> c >> d && (a || b || c || d)) {
        int ans = 1080;
        ans += 9 * ((a - b + 40) % 40);
        ans += 9 * ((c - b + 40) % 40);
        ans += 9 * ((c - d + 40) % 40);
        cout << ans << endl;
    }
    return 0;
}
