//
// Created by SNAKE on 2019-08-28.
//

#ifndef LEETCODE_DIY_H
#define LEETCODE_DIY_H

#include "csapp.h"

void prstr(const char *str,size_t size) {
    while(size--)
        printf("%c",*str++);
    printf("\n");
}

void* fast_memcpy(void* dst, const void* src, size_t len) {
    if (!(dst && src))
        return NULL;

    void* ret = dst;
    size_t size = len;

    size_t size64 = size >> 3;
    size &= 0x7;
    size_t size32 = size >> 2;
    size &= 0x3;
    size_t size16 = size >> 1;
    size &= 0x1;
    size_t size8 = size;

    if (dst <= src || dst >= src + len) {
        while (size64--) {
            *(uint64_t*) dst = *(uint64_t*) src;
            dst = (uint64_t*) dst + 1;
            src = (uint64_t*) src + 1;
        }
        while (size32--) {
            *(uint32_t*) dst = *(uint32_t*) src;
            dst = (uint32_t*) dst + 1;
            src = (uint32_t*) src + 1;
        }
        while (size16--) {
            *(uint16_t*) dst = *(uint16_t*) src;
            dst = (uint16_t*) dst + 1;
            src = (uint16_t*) src + 1;
        }
        while (size8--) {
            *(uint8_t*) dst = *(uint8_t*) src;
            dst = (uint8_t*) dst + 1;
            src = (uint8_t*) src + 1;
        }

    } else {
        src += len - 1;
        dst += len - 1;
        while (size64--) {
            *(uint64_t*) dst = *(uint64_t*) src;
            dst = (uint64_t*) dst - 1;
            src = (uint64_t*) src - 1;
        }
        while (size32--) {
            *(uint32_t*) dst = *(uint32_t*) src;
            dst = (uint32_t*) dst - 1;
            src = (uint32_t*) src - 1;
        }
        while (size16--) {
            *(uint16_t*) dst = *(uint16_t*) src;
            dst = (uint16_t*) dst - 1;
            src = (uint16_t*) src - 1;
        }
        while (size8--) {
            *(uint8_t*) dst = *(uint8_t*) src;
            dst = (uint8_t*) dst - 1;
            src = (uint8_t*) src - 1;
        }
    }
    return ret;
}


#endif //LEETCODE_DIY_H
