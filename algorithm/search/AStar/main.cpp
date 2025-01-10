#include "AStar.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    vector<int> map {
            0, 0, 0, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
    };
    Pos start{0, 0};
    Pos finish{3, 0};

    GridMap gridMap(map, 4, 4);
    int dist = AStar(gridMap, start, finish);
    cout << dist << endl;

    return 0;
}
