#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

vector<tuple<int, int>> walk = {{-2, 1}, {-1, 2}, {1, 2},   {2, 1},
                                {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

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

bool canAccess(int **arr, int size, pair<int, int> coordinate) {
  return !(coordinate.first >= size || coordinate.first < 0 ||
           coordinate.second >= size || coordinate.second < 0 ||
           arr[coordinate.first][coordinate.second]);
}

bool traversal(int **arr, int size, pair<int, int> current, int steps) {
  arr[current.first][current.second] = steps;
  if (steps == size * size)
    return true;

  for (auto [x, y] : walk) { // using c++17
    auto next = make_pair(current.first + x, current.second + y);
    if (canAccess(arr, size, next)) {
      auto isDone = traversal(arr, size, next, ++steps);
      if (isDone == false)
        --steps;
      else
        return isDone;
    }
  }
  arr[current.first][current.second] = 0;
  return false;
}

int main() {
  for (auto i : {1, 2, 3, 4, 5, 6, 7, 8}) {
    // the 9 is impossible, because the complacity is O(8^(n^2)).
    auto arr = makeMap(i);
    auto current = make_pair(0, 0);

    auto isDone = traversal(arr, i, current, 1);
    if (isDone)
      printMap(arr, i);
    else
      cout << "no solution" << endl;
    cout << endl;
    deleteMap(arr, i);
  }
  return 0;
}
