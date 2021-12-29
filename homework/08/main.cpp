#include <iostream>
#include "libs/huffmanLib.hpp"
using namespace std;

inline void getHelps()
{
    cout << "Usage: ./huffman.elf -option input_file\n" << endl;
    cout << "options:\n"
         << "    -c --compress\t to compress the input file\n"
         << "    -d --decompress\t to decompress the input file\n"
         << endl;
    cout << "Info: The output file name cannot be assigned!" << endl;
}

inline void wrongArgs()
{
    cout << "Wrong arugments!" << endl;
    getHelps();
}

int main(int argc, char *argv[])
{
    bool result = false;
    if (argc == 3 && (string(argv[1]) == string("--compress") ||
        string(argv[1]) == string("-c"))) {
        result = compress(string(argv[2]));
    } else if (argc == 3 && (string(argv[1]) == string("--decompress") ||
               string(argv[1]) == string("-d"))) {
        result = decompress(string(argv[2]));
    } else {
        wrongArgs();
    }

    cout << ((result) ? "Success!" : "Failed!") << endl;

    return result;
}