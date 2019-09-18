//
// Created by SNAKE on 2019-08-28.
//

#ifndef LEETCODE_MEMCPY_H
#define LEETCODE_MEMCPY_H

#include "include_for_c.h"

void prstr(const char* str, size_t n) {
  while (n--)
    printf("%c", *str++);
  printf("\n");
}

void*
assem_memcpy(void* dst, const void* src, size_t n) {
  const char* s;
  char* d;

  s = src;
  d = dst;
  if (s < d && s + n > d) {
    s += n;
    d += n;
    if ((int) s % 4 == 0 && (int) d % 4 == 0 && n % 4 == 0)
      asm volatile("std; rep movsl\n"
      ::"D" (d - 4), "S" (s - 4), "c" (n / 4) : "cc", "memory");
    else
      asm volatile("std; rep movsb\n"
      ::"D" (d - 1), "S" (s - 1), "c" (n) : "cc", "memory");
// Some versions of GCC rely on DF being clear
    asm volatile("cld":: : "cc");
  } else {
    if ((int) s % 4 == 0 && (int) d % 4 == 0 && n % 4 == 0)
      asm volatile("cld; rep movsl\n"
      ::"D" (d), "S" (s), "c" (n / 4) : "cc", "memory");
    else
      asm volatile("cld; rep movsb\n"
      ::"D" (d), "S" (s), "c" (n) : "cc", "memory");
  }
  return dst;
}

void* fast_memcpy(void* dst, const void* src, size_t len) {
  const char* s;
  char* d;

  s = src;
  d = dst;

  size_t size = len;
  size_t size64 = size >> 3;
  size &= 0x7;
  size_t size32 = size >> 2;
  size &= 0x3;
  size_t size16 = size >> 1;
  size &= 0x1;
  size_t size8 = size;

  if (d <= s || d >= s + len) {
    while (size64--)
      *(uint64_t*) (d += 8) = *(uint64_t*) (s += 8);
    while (size32--)
      *(uint32_t*) (d += 4) = *(uint32_t*) (s += 4);
    while (size16--)
      *(uint16_t*) (d += 2) = *(uint16_t*) (s += 2);
    while (size8--)
      *++d = *++s;
  } else {
    s += len;
    d += len;
    while (size8--)
      *--d = *--s;
    while (size16--)
      *(uint16_t*) (d -= 2) = *(uint16_t*) (s -= 2);
    while (size32--)
      *(uint32_t*) (d -= 4) = *(uint32_t*) (s -= 4);
    while (size64--)
      *(uint64_t*) (d -= 8) = *(uint64_t*) (s -= 8);
  }

  return dst;
}

void* slow_memcpy(void* dst, const void* src, size_t n) {
  const char* s;
  char* d;

  s = src;
  d = dst;
  if (s < d && s + n > d) {
    s += n;
    d += n;
    while (n-- > 0)
      *--d = *--s;
  } else
    while (n-- > 0)
      *d++ = *s++;

  return dst;
}

enum MC_CHOICE {
  BASIC, ASSEM, FAST, SLOW, C
};

void* (* mc[])(void* dst, const void* src, size_t n) ={
  memcpy,
  assem_memcpy,
  fast_memcpy,
  slow_memcpy
};
const char* mcstr[] = {
  "BASIC",
  "ASSEM",
  "FAST",
  "SLOW"
};


#endif //LEETCODE_MEMCPY_H
