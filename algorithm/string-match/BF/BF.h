//
// Created by Wingrez on 2021/8/16.
//

#ifndef BF_H
#define BF_H

#include <string>

int BF(const std::string &S, const std::string &T, int pos) {
    int m = S.length();
    int n = T.length();

    int i = pos, j = 0;
    while (i < m && j < n) {
        if (S[i] == T[j]) {
            j++;
        } else {
            j = 0;
        }
        i++;
    }
    if (j == n) {
        return i - j;
    }
    return -1;
}

#endif //BF_H
