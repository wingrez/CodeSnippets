//
// Created by Wingrez on 2021/8/16.
//

#ifndef SUNDAY_H
#define SUNDAY_H

#include <string>
#include <vector>

const int D = 128; // character variety

int Sunday(const std::string &S, const std::string &T, int pos) {
    int m = S.length();
    int n = T.length();

    std::vector<int> jump(D, n + 1);
    for (int i = 0; i < n; i++) {
        jump[T[i]] = n - i;
    }

    int i = pos;
    while (i <= m - n) {
        int j = 0;
        while (S[i + j] == T[j]) {
            ++j;
            if (j >= n) {
                return i;
            }
        }
        i += jump[S[i + n]];
    }

    return -1;
}

#endif //SUNDAY_H
