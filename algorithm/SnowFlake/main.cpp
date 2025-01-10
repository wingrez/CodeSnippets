#include <iostream>
#include <sys/time.h>
#include "SnowFlake.h"

using namespace std;

int main() {
    SnowFlake snowFlake;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    for (int i = 0; i < 10; i++) {
        cout << snowFlake.getNextId(tv.tv_sec) << endl;
    }

    return 0;
}
