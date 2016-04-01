/*
 * mglMessageHandlerLibManager.h
 *
 *  Created on: 08.02.2015
 *      Author: cromas
 */

#ifndef MGLMESSAGEHANDLERLIBMANAGER_H_
#define MGLMESSAGEHANDLERLIBMANAGER_H_


class mglMessageHandlerLibManager
{
public:
	~mglMessageHandlerLibManager();

	static mglMessageHandlerLibManager& Inst()
	{
		static mglMessageHandlerLibManager _instance;
		return _instance;
	};

	void init();

	shared_ptr<mglGuiObject> createGUIObject(mglValString* libname, mglValString* classname, DOMElement* configuration);
	shared_ptr<mglGuiObject> createGuiAction(mglValString* libname, mglValString* classname);

private:
	map<mglValString, shared_ptr<mglGuiLibHandle>> m_loadedGuiLibraries;

	map<mglValString, shared_ptr<mglMessageHandlerLibHandle>> m_loadedActionLibraries;
};


#endif /* MGLMESSAGEHANDLERLIBMANAGER_H_ */
