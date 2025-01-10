#include "RK.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string S = "Hello World!";
    string T = "World";

    cout << RK(S, T, 0) << endl;

    return 0;
}
