//
// Created by Wingrez on 2021/10/23.
//

#ifndef BFS_HPP
#define BFS_HPP

#include "GridMap.hpp"
#include <map>
#include <queue>
#include "iostream"

const int CAN_NOT_VISIT = -1;
const int VISITED = 1;

const int g_moveDirNum = 4;
const int g_moveDirX[g_moveDirNum] = {0, 1, 0, -1};
const int g_moveDirY[g_moveDirNum] = {1, 0, -1, 0};

struct BFSState {
    Pos pos;
    int step;
};

int BFS(GridMap &map, Pos start, Pos finish) {
    std::queue<BFSState> q;
    std::map<Pos, int> hasVisit;

    q.push({start, 0});
    hasVisit[start] = VISITED;

    while (!q.empty()) {
        BFSState cur = q.front();
        q.pop();

        for (int i = 0; i < g_moveDirNum; i++) {
            int nextX = cur.pos.x + g_moveDirX[i];
            int nextY = cur.pos.y + g_moveDirY[i];
            Pos nextPos{nextX, nextY};

            if (nextPos == finish) {
                return cur.step + 1;
            }

            if (map.isInArea(nextPos) && map.canVisit(nextPos) && hasVisit[nextPos] != VISITED) {
                q.push({nextPos, cur.step + 1});
                hasVisit[nextPos] = VISITED;
            }
        }
    }

    return CAN_NOT_VISIT;
}

#endif //BFS_HPP
