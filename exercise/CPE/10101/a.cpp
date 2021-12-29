#include <iostream>
using namespace std;

int main() {
    unsigned long long int input;
    while (cin >> input) {
        unsigned int kuti(0), lakh(0), hajar(0), shata(0);
        kuti = input / 10000000;
        if (kuti != 0)
            cout << kuti << " kuti ";
        input %= 10000000;

        lakh = input / 100000;
        if (lakh != 0)
            cout << lakh << " lakh ";
        input %= 100000;

        hajar = input / 1000;
        if (hajar != 0)
            cout << hajar << " hajar ";
        input %= 1000;

        shata = input / 100;
        if (shata != 0)
            cout << shata << " shata ";
        input %= 100;
        cout << input << endl;  //this will not ac
    }
    return 0;
}