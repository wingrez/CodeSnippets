#include <fstream>
#include <iostream>
#include "huffman.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: myHuffman [encode|decode] [source] [target]" << std::endl;
        return 0;
    }

    std::string mode(argv[1]);
    std::string srcFileName(argv[2]);
    std::string destFileName(argv[3]);

    std::ifstream fin(srcFileName, std::ios::in|std::ios::binary);
    std::ofstream fout(destFileName, std::ios::out|std::ios::binary);
    if (!fin || !fout) {
        std::cerr << "[Error] File open failed." << std::endl;
        return 0;
    }

    Huffman myHuffman;
    if (mode == "encode") {
        myHuffman.Encode(fin, fout);
        std::cout << "[Info] Encode success." << std::endl;
    } else if (mode == "decode"){
        myHuffman.Decode(fin, fout);
        std::cout << "[Info] Decode success." << std::endl;
    } else {
        std::cerr << "Usage: myHuffman [encode|decode] [source] [target]" << std::endl;
    }

    fin.close();
    fout.close();
    return 0;
}
