/*
 * mglDebug.h
 *
 *  Created on: 12.02.2014
 *      Author: cromas
 */

#ifndef MGLDEBUG_H_
#define MGLDEBUG_H_

#include "mglLogger.h"
#include "mglTechnicalException.h"

#define THROW_TECHNICAL_EXCEPTION(errno, msg) \
	LOG_EXCEPTION(errno << " " << msg); \
	throw mglTechnicalException(errno, msg);

#endif /* MGLDEBUG_H_ */
