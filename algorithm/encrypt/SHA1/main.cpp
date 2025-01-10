#include <fstream>
#include <iostream>
#include "sha1.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: mySHA1 [source]" << std::endl;
        return 0;
    }

    SHA1 sha1;
    std::cout << sha1.encode(argv[1]) << std::endl;

    return 0;
}
