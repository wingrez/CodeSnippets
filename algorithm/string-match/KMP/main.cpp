#include "KMP.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string S = "Hello World!";
    string T = "World";

    getNext(T);
    cout << KMP(S, T, 0) << endl;

    return 0;
}
