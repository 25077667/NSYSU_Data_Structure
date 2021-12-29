#include <iostream>
#include <vector>
using namespace std;

void carryFunction(vector<int> &current) {
  int carryValue = 0;
  for (vector<int>::iterator iter = current.begin(); iter != current.end();
       iter++) {
    (*iter) += carryValue;
    carryValue = (*iter) / 10;
    (*iter) %= 10;
  }
  while (carryValue) { // the last value to carry
    current.push_back(carryValue % 10);
    carryValue /= 10;
  }
}

void f(vector<int> &current, int n) {
  for (vector<int>::iterator iter = current.begin(); iter != current.end();
       iter++)
    (*iter) *= n;
  carryFunction(current);
}

void printVector(vector<int> &current, int n) {
  cout << n << "!=";
  for (vector<int>::iterator iter = current.end() - 1; iter >= current.begin();
       iter--)
    cout << *iter;
  cout << endl;
}

void cleanVector(vector<int> &current) {
  current.clear();
  current.shrink_to_fit();
  current.push_back(1);
}

int main() {
  vector<int> current;
  cleanVector(current);
  int n;
  while (cin >> n && n) {
    for (int i = 1; i <= n; i++) {
      f(current, i);
      printVector(current, i);
    }
    cout << endl;
    cleanVector(current);
  }
  return 0;
}
