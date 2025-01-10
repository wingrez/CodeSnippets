//
// Created by Wingrez on 2022/6/22.
//

#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "SnowFlake.h"

#define MAX_NEXT 0b1111111111111111L
#define OFFSET 946656000L

SnowFlake::SnowFlake() {
    m_offset = 0;
    m_last = 0;
    m_shareid = getServerId() & 0x1F;
}

int64_t SnowFlake::getServerId() {
    struct hostent *host = nullptr;
    char name[256];
    char ip[32];

    gethostname(name, sizeof(name));
    host = gethostbyname(name);

    if (inet_ntop(host->h_addrtype, host->h_addr_list[0], ip, sizeof(ip)) == nullptr) {
        return -1;
    }

    return htonl(inet_addr(ip));
}

int64_t SnowFlake::getNextId(int64_t epoch) {
    if (epoch < m_last) {
        epoch = m_last;
    }

    if (m_last != epoch) {
        m_last = epoch;
        m_offset = 0;
    }

    m_offset++;
    int64_t next = m_offset & MAX_NEXT;
    if (next == 0) {
        return getNextId(epoch + 1);
    }

    return generateId(epoch, next, m_shareid);
}

int64_t SnowFlake::generateId(int64_t epoch, int64_t next, int64_t shareid) {
    return ((epoch - OFFSET) << 21 | (next << 5) | shareid);
}