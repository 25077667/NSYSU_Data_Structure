#include <cstring>
#include <iostream>

struct Point {
    int vertical, horizon;
};

int** allocArray(int size) {
    int** arr = new int*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];
        memset(arr[i], 0, sizeof(int) * size);
    }
    return arr;
}

void freeArray(int** arr, int size) {
    for (int i = 0; i < size; i++)
        delete[] arr[i];
}

void printArray(int** arr, int size) {
    for (int i = 0; i < size && printf("\n"); i++)
        for (int j = 0; j < size; j++)
            printf("%2d ", arr[i][j]);
}

void magic_square(int size) {
    auto arr = allocArray(size);
    Point current = {.vertical = 0, .horizon = size / 2};
    int counter = 1;
    while (counter <= size * size) {
        if (arr[current.vertical][current.horizon] != 0) {
            if (current.horizon == current.vertical && current.horizon == size - 1) {
                current.horizon = 0;
                current.vertical = 1;
            } else {
                current.vertical += 2;
                current.horizon++;
            }
        }

        arr[current.vertical][current.horizon] = counter++;
        current.vertical--;
        current.horizon--;
        if (current.vertical < 0) current.vertical = size - 1;
        if (current.horizon < 0) current.horizon = size - 1;
    }
    printArray(arr, size);
    freeArray(arr, size);
}

int main() {
    for (int i = 1; i < 10; i += 2) {
        printf("\n");
        printf("This is %d order of magic square\n", i);
        magic_square(i);
        printf("\n");
    }
    return 0;
}