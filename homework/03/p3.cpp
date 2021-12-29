#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Dish {
public:
  Dish(int x, int y, int _orientedFrom) {
    this->destination = make_pair(x, y);
    this->orientedFrom = _orientedFrom;
  }
  Dish(pair<int, int> _destination, int _orientedFrom) {
    this->destination = _destination;
    this->orientedFrom = _orientedFrom;
  }
  pair<int, int> destination;
  int orientedFrom;
};

class Stack {
public:
  Stack();
  void push(const Dish &);
  void pop();
  bool empty();
  int size();
  const Dish top();

private:
  vector<Dish> _stack;
};

int **makeMap(int n) {
  int **arr = new int *[n];
  for (int i = 0; i < n; i++) {
    arr[i] = new int[n];
    memset(arr[i], 0, sizeof(int) * n);
  }
  return arr;
}

void deleteMap(int **arr, int size) {
  for (int i = 0; i < size; i++)
    delete[] arr[i];
}

void printMap(int **arr, int size) {
  for (int j = 0; j < size; j++) {
    for (int k = 0; k < size; k++)
      cout << arr[j][k] << " ";
    cout << endl;
  }
}

bool canAccess(int **arr, int size, int x, int y) {
  return !(x >= size || x < 0 || y >= size || y < 0 || arr[x][y]);
}

int main() {
  for (int i = 1; i <= 6; i++) {
    Stack A;
    int **arr = makeMap(i);
    pair<int, int> current{0, 0};
    int steps = 1, hadView;
    bool isBack = false;

    A.push(Dish(current, 0));
    arr[0][0] = steps;
    while (true) {
      if (steps == i * i) {
        printMap(arr, i);
        cout << endl;
        break;
      }
      if (A.empty()) {
        cout << "no solution" << endl;
        break;
      }

      if (!isBack)
        hadView = 0;
      // K1
      if (canAccess(arr, i, current.first - 2, current.second + 1) &&
          hadView < 1) {
        current = make_pair(current.first - 2, current.second + 1);
        A.push(Dish(current, 1));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      }
      // K2
      else if (canAccess(arr, i, current.first - 1, current.second + 2) &&
               hadView < 2) {
        current = make_pair(current.first - 1, current.second + 2);
        A.push(Dish(current, 2));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      }
      // K3
      else if (canAccess(arr, i, current.first + 1, current.second + 2) &&
               hadView < 3) {
        current = make_pair(current.first + 1, current.second + 2);
        A.push(Dish(current, 3));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      }
      // K4
      else if (canAccess(arr, i, current.first + 2, current.second + 1) &&
               hadView < 4) {
        current = make_pair(current.first + 2, current.second + 1);
        A.push(Dish(current, 4));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      }
      // K5
      else if (canAccess(arr, i, current.first + 2, current.second - 1) &&
               hadView < 5) {
        current = make_pair(current.first + 2, current.second - 1);
        A.push(Dish(current, 5));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      }
      // K6
      else if (canAccess(arr, i, current.first + 1, current.second - 2) &&
               hadView < 6) {
        current = make_pair(current.first + 1, current.second - 2);
        A.push(Dish(current, 6));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      }
      // K7
      else if (canAccess(arr, i, current.first - 1, current.second - 2) &&
               hadView < 7) {
        current = make_pair(current.first - 1, current.second - 2);
        A.push(Dish(current, 7));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      }
      // K8
      else if (canAccess(arr, i, current.first - 2, current.second - 1) &&
               hadView < 8) {
        current = make_pair(current.first - 2, current.second - 1);
        A.push(Dish(current, 8));
        arr[current.first][current.second] = ++steps;
        isBack = false;
      } else {
        arr[current.first][current.second] = 0;
        hadView = A.top().orientedFrom;
        A.pop();
        current = A.top().destination;
        steps--;
        isBack = true;
      }
    }
    deleteMap(arr, i);
  }
  return 0;
}

Stack::Stack() { this->_stack.clear(); }

void Stack::push(const Dish &_newDish) { this->_stack.push_back(_newDish); }

void Stack::pop() { this->_stack.pop_back(); }

bool Stack::empty() { return (this->_stack.size() == 0); }

int Stack::size() { return this->_stack.size(); }

const Dish Stack::top() { return this->_stack.back(); }