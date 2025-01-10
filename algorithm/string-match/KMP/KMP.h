//
// Created by Wingrez on 2021/8/16.
//

#ifndef KMP_H
#define KMP_H

#include <string>

const int MAXL_S = 1024;
const int MAXL_T = 1024;
int nxt[MAXL_T];

void getNext(const std::string &T) {
    // 计算next数组
    int n = T.length();
    nxt[0] = -1;
    int i = 0, j = -1;
    while (i < n - 1) {
        if (j == -1 || T[i] == T[j]) nxt[++i] = ++j;
        else j = nxt[j];
    }
}

void getNextOpt(const std::string &T) {
    // 计算优化的next数组
    int n = T.length();
    int i = 0, j = -1;
    nxt[0] = -1;
    while (i < n - 1) { // 此处i<n也可，此时查询整个字符串的循环节
        if (j == -1 || T[i] == T[j]) {
            ++i; ++j;
            nxt[i] = (T[i] == T[j] ? nxt[j] : j);
        } else {
            j = nxt[j];
        }
    }
}

int KMP(const std::string &S, const std::string &T, int pos) {
    // 已经计算出next，返回T在S中第pos个字符之后的位置
    int m = S.length();
    int n = T.length();
    int i = pos, j = 0;
    while (i < m && j < n) {
        if (j == -1 || S[i] == T[j]) {
            ++i; ++j;
        }
        else {
            j = nxt[j];
        }
    }
    if (j == n) return i - j;
    return -1;
}

#endif //KMP_H
