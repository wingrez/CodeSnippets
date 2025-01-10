#include <fstream>
#include <iostream>
#include "md5.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: myMD5 [source]" << std::endl;
        return 0;
    }

    MD5 md5;
    std::cout << md5.encode(argv[1]) << std::endl;

    return 0;
}
