#include <utils_misc/mutex.hh>
#include <app_config/proj_app_cfg.h>

#ifdef USE_MUTEX
RecMutex txtio_mutex;
#else
MutexDummy txtio_mutex;
#endif
