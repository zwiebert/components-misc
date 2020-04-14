/*
 * mutex.h
 *
 *  Created on: 14.04.2020
 *      Author: bertw
 */

#ifndef COMPONENTS_TXTIO_TXTIO_MUTEX_H_
#define COMPONENTS_TXTIO_TXTIO_MUTEX_H_

#include "app_config/proj_app_cfg.h"

#ifdef USE_TXTIO_MUTEX
void txtio_mutexSetup();
bool txtio_mutexTake();
bool txtio_mutexTakeTry();
void txtio_mutexGive();
#else
#define txtio_mutexSetup()
#define txtio_mutexTake() true
#define txtio_mutexTakeTry() true
#define txtio_mutexGive()
#endif


#endif /* COMPONENTS_TXTIO_TXTIO_MUTEX_H_ */
