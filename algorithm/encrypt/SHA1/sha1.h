//
// Created by Wingrez on 2021/7/25.
//

#ifndef SHA1_H
#define SHA1_H

#include <string>

#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

class SHA1 {
public:
    SHA1() = default;

    ~SHA1() = default;

    std::string encode(std::string input);

private:
    void transform(unsigned int W[80]);

    unsigned int state[5]{ 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };

    const std::string hexs[16]{"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
};


#endif //SHA1_H
