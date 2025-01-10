//
// Created by Wingrez on 2021/7/25.
//

#include "des.h"
#include <iostream>
#include <vector>

std::string DES::encrypt(const std::string &source, const std::string &key) {
    if (source.size() != 8 || key.size() != 8) {
        throw "Illegal length, len must be 8";
    }
    std::vector<int> srcBits, keyBits;
    str2bits(source, srcBits);
    str2bits(key, keyBits);

    // 初始置换
    initialPermutation(srcBits);
    // 将置换后的明文划分成左右两部分
    std::vector<int> leftSrcBits(srcBits.begin(), srcBits.begin() + 32);
    std::vector<int> rightSrcBits(srcBits.begin() + 32, srcBits.end());

    // 获取16个子密钥
    PC1Permutation(keyBits);
    std::vector<int> leftKeyBits(keyBits.begin(), keyBits.begin() + 28);
    std::vector<int> rightKeyBits(keyBits.begin() + 28, keyBits.end());
    std::vector<std::vector<int>> subKeys(16);
    for (int i = 0; i < 16; i++) {
        leftMove(leftKeyBits, leftMoveTimes[i]);
        leftMove(rightKeyBits, leftMoveTimes[i]);
        subKeys[i].insert(subKeys[i].end(), leftKeyBits.begin(), leftKeyBits.end());
        subKeys[i].insert(subKeys[i].end(), rightKeyBits.begin(), rightKeyBits.end());
        PC2Permutation(subKeys[i]);
//        for (auto v: subKeys[i]) {
//            std::cout << v << " ";
//        }
//        std::cout << std::endl;
    }

    // 明文16轮迭代
    for (int i = 0; i < 16; i++) {
        EPermutation(rightSrcBits);
        f(rightSrcBits, subKeys[i]);
        SPermutation(rightSrcBits);
        PPermutation(rightSrcBits, leftSrcBits);
        swap(rightSrcBits, leftSrcBits);
    }

    // 将左边和右边合并
    std::vector<int> resBits(leftSrcBits.begin(), leftSrcBits.end());
    resBits.insert(resBits.end(), rightSrcBits.begin(), rightSrcBits.end());

    // 逆置换
    IP1Permutation(resBits);

    std::string resStr;
    for (int i = 0; i < 16; i++) {
        unsigned int t = 0;
        for (int j = 0; j < 4; j++) {
            t <<= 1;
            t += resBits[i * 4 + j];
        }
        resStr += hexs[t];
    }

    return resStr;
}

std::string DES::decrypt(const std::string &source, const std::string &key) {
    return "0";
}

void DES::str2bits(const std::string &str, std::vector<int> &bits) {
    for (auto ch: str) {
        for (int i = 0; i < 8; i++) {
            bits.push_back((ch >> (7 - i)) & 1);
        }
    }
}

void DES::initialPermutation(std::vector<int> &srcBits) {
    std::vector<int> res(64);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            res[i * 8 + j] = srcBits[IP[i][j] - 1];
        }
    }
    srcBits = res;
}

void DES::PC1Permutation(std::vector<int> &keyBits) {
    std::vector<int> res(56);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            res[i * 7 + j] = keyBits[PC1[i][j] - 1];
        }
    }
    keyBits = res;
}

void DES::leftMove(std::vector<int> &keyBits, int times) {
    for (int i = 0; i < times; i++) {
        int t = keyBits[0];
        for (int j = 1; j < keyBits.size(); j++) {
            keyBits[j - 1] = keyBits[j];
        }
        keyBits[keyBits.size() - 1] = t;
    }
}

void DES::PC2Permutation(std::vector<int> &subKeyBits) {
    std::vector<int> res(48);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            res[i * 6 + j] = subKeyBits[PC2[i][j] - 1];
        }
    }
    subKeyBits = res;
}

void DES::EPermutation(std::vector<int> &rightSrcBits) {
    std::vector<int> res(48);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            res[i * 6 + j] = rightSrcBits[E[i][j] - 1];
        }
    }
    rightSrcBits = res;
}

void DES::f(std::vector<int> &rightSrcBits, const std::vector<int> &subKeyBits) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            rightSrcBits[i * 6 + j] ^= subKeyBits[i * 6 + j];
        }
    }
}

void DES::SPermutation(std::vector<int> &rightSrcBits) {
    std::vector<int> res(32);
    for (int i = 0; i < 8; i++) {
        int row = rightSrcBits[6 * i] * 2 + rightSrcBits[6 * i + 5];
        int col = rightSrcBits[6 * i + 1] * 8 +  rightSrcBits[6 * i + 2] * 4 + rightSrcBits[6 * i + 3] * 2 + rightSrcBits[6 * i + 4];
        res[i * 4] = (S[i][row][col] >> 3) & 1;
        res[i * 4 + 1] = (S[i][row][col] >> 2) & 1;
        res[i * 4 + 2] = (S[i][row][col] >> 1) & 1;
        res[i * 4 + 3] = S[i][row][col] & 1;
    }
    rightSrcBits = res;
}

void DES::PPermutation(const std::vector<int> &rightSrcBits, std::vector<int> &leftSrcBits) {
    std::vector<int> res(32);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            leftSrcBits[i * 4 + j] ^= rightSrcBits[P[i][j] - 1];
        }
    }
}

void DES::IP1Permutation(std::vector<int> &srcBits) {
    std::vector<int> res(64);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            res[i * 8 + j] = srcBits[IP1[i][j] - 1];
        }
    }
    srcBits = res;
}




