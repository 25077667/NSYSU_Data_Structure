#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct Walk {
  int x[9] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
  int y[9] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
} walk;

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
  for (int i = 0; i < n; i++)
    arr[i] = new int[n]();
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
  for (int i = 1; i <= 8; i++) {
    Stack A;
    int **arr = makeMap(i);
    pair<int, int> current{0, 0};
    int steps = 1, hadView;

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

      int j;
      for (j = hadView + 1; j < 9; j++) {
        if (canAccess(arr, i, current.first + walk.x[j],
                      current.second + walk.y[j])) {
          current =
              make_pair(current.first + walk.x[j], current.second + walk.y[j]);
          A.push(Dish(current, j));
          arr[current.first][current.second] = ++steps;
          hadView = 0;
          break;
        }
      }
      if (j == 9) {
        arr[current.first][current.second] = 0;
        hadView = A.top().orientedFrom;
        A.pop();
        current = A.top().destination;
        steps--;
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