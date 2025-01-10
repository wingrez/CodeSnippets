//
// Created by Wingrez on 2021/10/23.
//

#ifndef GRID_MAP_HPP
#define GRID_MAP_HPP

#include <vector>
#include <string>

struct Pos {
    int x;
    int y;

    bool operator == (const Pos &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator < (const Pos &rhs) const {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
};

struct Grid {
    Pos pos;
    int data;
};

const int BLANK = 0;
const int WALL = 1;

class GridMap {
public:
    GridMap(std::vector<int> map, int width, int height) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                _map.push_back(Grid{i, j, map[i * width + j]});
            }
        }
        _width = width;
        _height = height;
    }

    bool isInArea(Pos pos) {
        return pos.x >= 0 && pos.x < _width && pos.y >= 0 && pos.y < _height;
    }

    bool canVisit(Pos pos) {
        return _map[pos.x * _width + pos.y].data == BLANK;
    }

    std::string toString() {
        std::string ret;
        for (int i = 0; i < _width; i++) {
            for (int j = 0; j < _height; j++) {
                ret += std::to_string(_map[i * _width + j].data) + " ";
            }
            ret += "\n";
        }
        return ret;
    }

private:    
    std::vector<Grid> _map;
    int _width;
    int _height;
};

#endif //GRID_MAP_HPP