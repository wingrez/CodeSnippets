//
// Created by Wingrez on 2021/10/23.
//

#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "GridMap.hpp"
#include <vector>
#include <algorithm>

const int CAN_NOT_VISIT = -1;

const int g_moveDirNum = 4;
const int g_moveDirX[g_moveDirNum] = {0, 1, 0, -1};
const int g_moveDirY[g_moveDirNum] = {1, 0, -1, 0};

struct AStarState {
    Pos pos;
    int step;
    int g;
    int h;

    int f() const {
        return g + h;
    }

    bool operator < (const AStarState &rhs) const {
        return f() < rhs.f();
    }
};

std::vector<AStarState> openList;
std::vector<AStarState> closeList;

int findInOpen(Pos pos) {
    for (int i = 0; i < openList.size(); i++) {
        if (openList[i].pos == pos) {
            return i;
        }
    }
    return -1;
}

int findInClose(Pos pos) {
    for (int i = 0; i < closeList.size(); i++) {
        if (closeList[i].pos == pos) {
            return i;
        }
    }
    return -1;
}

int H(Pos start, Pos finish) {
    return abs(start.x - finish.x) + abs(start.y - finish.y);
}

int AStar(GridMap &map, Pos start, Pos finish) {
    openList.clear();
    closeList.clear();
    openList.push_back({start, 0, 0, -1});

    while (!openList.empty()) {
        AStarState s = openList.front();
        openList.erase(openList.begin());
        closeList.push_back(s);

        if (s.pos == finish) {
            return s.step;
        }

        for (int i = 0; i < g_moveDirNum; i++) {
            int nextX = s.pos.x + g_moveDirX[i];
            int nextY = s.pos.y + g_moveDirY[i];
            Pos nextPos{nextX, nextY};

            if (!map.isInArea(nextPos) || !map.canVisit(nextPos)) {
                continue;
            }

            if (findInClose(nextPos) != -1) {
                continue;
            }

            int nextG = s.h + 1;
            int idx = findInOpen(nextPos);
            if (idx == -1) {
                openList.push_back({nextPos, s.step + 1, nextG, H(nextPos, finish)});
            } else if (nextG < openList[idx].g) {
                openList[idx].g = nextG;
            }
        }

        std::sort(openList.begin(), openList.end());
    }

    return CAN_NOT_VISIT;
}


#endif //ASTAR_HPP
