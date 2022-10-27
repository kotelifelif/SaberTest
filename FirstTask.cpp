#include <iostream>

using namespace std;

template <class T>
void print_binary(T number) {
    int bits_size = sizeof(T) * 8;

    for (int bits_offset = bits_size - 1; bits_offset >= 0; bits_offset--)
    {
        int digit = (number >> bits_offset) & 1;
        cout << digit;
    }
    cout << endl;
}