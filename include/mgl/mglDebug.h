/*
 * mglDebug.h
 *
 *  Created on: 12.02.2014
 *      Author: chuhlich
 */

#ifndef MGLDEBUG_H_
#define MGLDEBUG_H_

#include "mglLogger.h"
#include "mglTechnicalException.h"

#define THROW_TECHNICAL_EXCEPTION(errno, msg) \
	do { \
		std::stringstream line; \
		line << msg; \
		throw mglTechnicalException(errno, line.str()); \
	} \
	while (false); \
	LOG_EXCEPTION << "\n########## EXCEPTION Exception exception ##########\n## Errnr.: " << errno << "\n## Msg.: " << msg << "\n########## ######### ######### ######### ##########\n";

#endif /* MGLDEBUG_H_ */
