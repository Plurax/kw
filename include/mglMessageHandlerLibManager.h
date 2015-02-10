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

	mglGuiObject* createGUIObject(mglValString* libname, mglValString* classname, DOMElement* configuration);
	mglMessageHandler* createGuiAction(mglValString* libname, mglValString* classname);

private:
	map<mglValString, mglGuiLibHandle*> m_loadedGuiLibraries;

	map<mglValString, mglMessageHandlerLibHandle*> m_loadedActionLibraries;
};


#endif /* MGLMESSAGEHANDLERLIBMANAGER_H_ */
