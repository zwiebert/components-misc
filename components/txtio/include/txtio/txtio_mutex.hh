#pragma once

#include <app_config/proj_app_cfg.h>
#include <utils_misc/mutex.hh>

#ifdef USE_MUTEX
extern RecMutex txtio_mutex;
#else
extern MutexDummy txtio_mutex;
#endif


