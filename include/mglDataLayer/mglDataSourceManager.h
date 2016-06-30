/*
 * mglDataLayer.h
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */

#ifndef MGLDATALAYER_H_
#define MGLDATALAYER_H_

#include "mglValues/mglValString.h"
#include <stdio.h>
#include <map>
#include <vector>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdexcept>

#include <json.hpp>

#ifdef WIN32
#include "Windows.h"
#else
#include <dlfcn.h>
#endif

#include "mglDataLayer/mglDataSourceManager.h"
#include "mglDataLayer/mglDataSourceFactory.h"
#include "mglDataLayer/mglDataLibHandle.h"

using json = nlohmann::json;

class mglDataSourceManager
{
public:
	~mglDataSourceManager();

	static mglDataSourceManager& Inst()
	{
		static mglDataSourceManager _instance;
		return _instance;
	};

	void init();

	shared_ptr<mglDataSource> createDataSource(shared_ptr<mglValString>& libname, shared_ptr<mglValString>& classname, json configuration);

private:
	map<mglValString, shared_ptr<mglDataLibHandle>> m_loadedDataSources;

};

#endif /* MGLDATALAYER_H_ */
