//
// Created by Wingrez on 2021/10/23.
//

#ifndef DFS_HPP
#define DFS_HPP

#include "GridMap.hpp"
#include <map>
#include <queue>
#include "iostream"

const int CAN_NOT_VISIT = -1;
const int VISITED = 1;

const int g_moveDirNum = 4;
const int g_moveDirX[g_moveDirNum] = {0, 1, 0, -1};
const int g_moveDirY[g_moveDirNum] = {1, 0, -1, 0};

std::map<Pos, int> hasVisit;

void DFS_aux(GridMap &map, Pos start, Pos finish, int curStep, int &minStep) {
    if (start == finish) {
        if (minStep == -1 || curStep < minStep) {
            minStep = curStep;
        }
        return;
    }

    for (int i = 0; i < g_moveDirNum; i++) {
        int nextX = start.x + g_moveDirX[i];
        int nextY = start.y + g_moveDirY[i];
        Pos nextPos{nextX, nextY};

        if (map.isInArea(nextPos) && map.canVisit(nextPos) && hasVisit[nextPos] != VISITED) {
            hasVisit[nextPos] = VISITED;
            DFS_aux(map, nextPos, finish, curStep + 1, minStep);
            hasVisit[nextPos] = !VISITED;
        }
    }
}

int DFS(GridMap &map, Pos start, Pos finish) {
    int minStep = -1;
    hasVisit[start] = VISITED;
    DFS_aux(map, start, finish, 0, minStep);
    return minStep;
}

#endif //DFS_HPP
