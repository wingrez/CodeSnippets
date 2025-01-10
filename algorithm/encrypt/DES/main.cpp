#include <iostream>
#include "des.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: myDES [encrypt|decrypt] [source] [key]" << std::endl;
        return 0;
    }

    std::string mode = std::string(argv[1]);
    std::string source = std::string(argv[2]);
    std::string key = std::string(argv[3]);
    DES des;

    try{
        if (mode == "encrypt") {
            std::cout << des.encrypt(source, key) << std::endl;
        } else if (mode == "decrypt") {
            std::cout << des.decrypt(source, key) << std::endl;
        } else {
            std::cerr << "Usage: myDES [encrypt|decrypt] [source] [key]" << std::endl;
        }
    } catch (const char *err) {
        std::cerr << err << std::endl;
    }

    return 0;
}
