#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main() {
    vector<int> a, b, c;

    for (auto i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
        a.push_back(i);
        b.push_back(i + 100);
    }

    for (auto i : {200, 201, 202, 203})
        b.push_back(i);

    auto bigger = max(a, b);
    auto smaller = min(a, b);

    int recorder = 0;
    for (auto iter = smaller.begin(); iter != smaller.end(); iter++) {
        recorder = distance(smaller.begin(), iter);
        //cout << recorder << endl;
        c.push_back(bigger.at(recorder));
        c.push_back(*iter);
    }

    for (auto i : vector<int>(bigger.begin() + recorder, bigger.end()))
        c.push_back(i);

    for (auto i : c)
        cout << i << " ";
    cout << endl;
    
    return 0;
}

/*
About time complexity:
because max and min is calling vector.size()
and the vector.size() complexity is constant[1]
therefore this program total complexity is max(n, m) for n, m are the size of vector.

ref.
[1] https://en.cppreference.com/w/cpp/container/vector/size
*/