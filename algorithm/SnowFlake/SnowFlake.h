//
// Created by Wingrez on 2022/6/22.
//

#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H


#include <cstdint>

class SnowFlake {
public:
    SnowFlake();
    ~SnowFlake() = default;
    int64_t getNextId(int64_t epoch);

private:
    int64_t getServerId();
    int64_t generateId(int64_t epoch, int64_t next, int64_t shareid);
    int64_t m_offset;
    int64_t m_last;
    int64_t m_shareid;
};


#endif //SNOWFLAKE_H
