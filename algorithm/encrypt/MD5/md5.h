//
// Created by Wingrez on 2021/7/20.
//

#ifndef MD5_H
#define MD5_H

#include <string>

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, ac) {          \
    (a) += F ((b), (c), (d)) + (x) + (ac);  \
    (a) = ROTATE_LEFT ((a), (s));           \
    (a) += (b);                             \
}

#define GG(a, b, c, d, x, s, ac) {          \
    (a) += G ((b), (c), (d)) + (x) + (ac);  \
    (a) = ROTATE_LEFT ((a), (s));           \
    (a) += (b);                             \
}

#define HH(a, b, c, d, x, s, ac) {          \
    (a) += H ((b), (c), (d)) + (x) + (ac);  \
    (a) = ROTATE_LEFT ((a), (s));           \
    (a) += (b);                             \
}

#define II(a, b, c, d, x, s, ac) {          \
    (a) += I ((b), (c), (d)) + (x) + (ac);  \
    (a) = ROTATE_LEFT ((a), (s));           \
    (a) += (b);                             \
}

class MD5 {
public:
    MD5() = default;

    ~MD5() = default;

    std::string encode(std::string input);

private:
    void transform(unsigned int g[16]);

    const int S11 = 7;
    const int S12 = 12;
    const int S13 = 17;
    const int S14 = 22;

    const int S21 = 5;
    const int S22 = 9;
    const int S23 = 14;
    const int S24 = 20;

    const int S31 = 4;
    const int S32 = 11;
    const int S33 = 16;
    const int S34 = 23;

    const int S41 = 6;
    const int S42 = 10;
    const int S43 = 15;
    const int S44 = 21;

    const std::string hexs[16]{"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};

    unsigned int state[4]{0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
};

#endif //MD5_H
