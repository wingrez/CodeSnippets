//
// Created by Wingrez on 2021/7/25.
//

#include "sha1.h"
#include <vector>

std::string SHA1::encode(std::string input) {
    std::vector<unsigned char> bytes(input.begin(), input.end());
    unsigned int bytesLen = bytes.size();

    // 补齐448位
    int restByteNum = bytesLen % 64;
    if (restByteNum < 56) {
        bytes.push_back(1 << 7);
        for (int i = 0; i < 56 - restByteNum - 1; i++) {
            bytes.push_back(0);
        }
    } else if (restByteNum > 56) {
        bytes.push_back(1 << 7);
        for (int i = 0; i < 64 - restByteNum - 1 + 56; i++) {
            bytes.push_back(0);
        }
    }

    // 追加64位信息长度，当前实现仅能处理2^32 - 1位长度的数据
    unsigned int len = bytesLen << 3;
    for (int i = 0; i < 4; i++) {
        bytes.push_back(0);
    }
    for (int i = 4; i < 8; i++) {
        bytes.push_back(len >> 24);
        len <<= 8;
    }

    int newBytesLen = bytes.size();
    for (int i = 0; i < newBytesLen / 64; i++) {
        // 对512b分成16组，每组32b，再扩展成80组
        unsigned int W[80];
        for (int j = 0; j < 16; j++) {
            W[j] = bytes[i * 64 + j * 4] << 24 |
                   bytes[i * 64 + j * 4 + 1] << 16 |
                   bytes[i * 64 + j * 4 + 2] << 8 |
                   bytes[i * 64 + j * 4 + 3];
        }
        for (int j = 16; j < 80; j++) {
            W[j] = rol(W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16], 1);
        }
        transform(W);
    }

    std::string res;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            res += hexs[(state[i] >> 28) & 0x0F] + hexs[(state[i] >> 24) & 0x0F];
            state[i] <<= 8;
        }
    }

    return res;
}

void SHA1::transform(unsigned int *W) {
    unsigned int A = state[0],
            B = state[1],
            C = state[2],
            D = state[3],
            E = state[4];
    unsigned int K[] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };
    unsigned int temp;

    // 第一轮
    for (int i = 0; i < 20; i++) {
        temp = rol(A, 5) + ((B & C) | ((~B) & D)) + E + W[i] + K[0];
        E = D;
        D = C;
        C = rol(B, 30);
        B = A;
        A = temp;
    }

    // 第二轮
    for (int i = 20; i < 40; i++) {
        temp = rol(A, 5) + (B ^ C ^ D) + E + W[i] + K[1];
        E = D;
        D = C;
        C = rol(B, 30);
        B = A;
        A = temp;
    }

    // 第三轮
    for (int i = 40; i < 60; i++) {
        temp = rol(A, 5) + ((B & C) | (B & D) | (C & D)) + E + W[i] + K[2];
        E = D;
        D = C;
        C = rol(B, 30);
        B = A;
        A = temp;
    }

    // 第四轮
    for (int i = 60; i < 80; i++) {
        temp = rol(A, 5) + (B ^ C ^ D) + E + W[i] + K[3];
        E = D;
        D = C;
        C = rol(B, 30);
        B = A;
        A = temp;
    }

    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
    state[4] += E;
}