/*
 * kwDebug.h
 *
 *  Created on: 12.02.2014
 *      Author: chuhlich
 */

#ifndef KWDEBUG_H_
#define KWDEBUG_H_

#include "kw/kwLogger.h"
#include "kw/kwTechnicalException.h"

#define THROW_TECHNICAL_EXCEPTION(errno, msg) \
	do { \
		std::stringstream line; \
		line << msg; \
		throw kwTechnicalException(errno, line.str()); \
	} \
	while (false); \
	LOG_EXCEPTION << "\n########## EXCEPTION Exception exception ##########\n## Errnr.: " << errno << "\n## Msg.: " << msg << "\n########## ######### ######### ######### ##########\n";

#endif /* KWDEBUG_H_ */
