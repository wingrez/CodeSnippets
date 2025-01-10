//
// Created by Wingrez on 2021/8/16.
//

#ifndef RK_H
#define RK_H

#include <string>

const int P = 100019; // large prime number

bool isStrEqual(const std::string &S, int from, const std::string &T, int len) {
    for (int i = from, j = 0; i < S.length() && i < from + len; i++, j++) {
        if (S[i] != T[j]) {
            return false;
        }
    }
    return true;
}

int RK(const std::string &S, const std::string &T, int pos) {
    int m = S.length();
    int n = T.length();

    unsigned int S_hash = S[0];
    unsigned int T_hash = T[0];
    for (int i = 1; i < n; i++) {
        S_hash = (S_hash + S[i]) % P;
        T_hash = (T_hash + T[i]) % P;
    }

    for (int i = pos; i <= m - n; i++) {
        if (S_hash == T_hash) {
            if (isStrEqual(S, i, T, n)) {
                return i;
            }
        }
        if (i + n < m) {
            S_hash = (S_hash - S[i] + S[i + n]) % P;
        }
    }

    return -1;
}

#endif //RK_H
