#include "BF.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string S = "Hello World!";
    string T = "World";

    cout << BF(S, T, 0) << endl;

    return 0;
}
