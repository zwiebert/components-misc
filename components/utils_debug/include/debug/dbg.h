#pragma once

#include "log.h"
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#ifdef __cplusplus
extern "C++" {
  template<typename T>
    T rando(T low_limit, T high_limit) {
      return low_limit + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (high_limit - low_limit)));
   }
#endif

extern int unit_testing;
#define UNIT_TEST (unit_testing+0)

void abort_precond(const char *msg, int line);
void abort_postcond(const char *msg, int line);

#if defined NO_PRECOND || defined DISTRIBUTION
#define precond(x)
#else
#define precond(x)  assert(x)
#endif

#if defined NO_POSTCOND  || defined DISTRIBUTION
#define postcond(x)
#else
#define postcond(x) assert(x)
#endif

#ifdef __cplusplus
  }
#endif
