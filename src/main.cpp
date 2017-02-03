/*
 * main.cpp
 *
 *  Created on: 22.11.2016
 *      Author: chuhlich
 */

#include <iostream>
using namespace std;
#include "mglBase.h"

#include <unistd.h>



int main() {
    mglSystem& MainSystem = mglSystem::Inst();
    mglValString configfile = mglValString("config/Configuration.json");
    MainSystem.init(configfile);

    bool done = false;

    while (!done)
    {
    	auto newMess  = make_shared<mglMessage>(1);
    	newMess->setMessageText("TestMessage!");
    	MainSystem.addMessage(newMess);

    	MainSystem.processMessages();
    	usleep(1000000);
    }

    return 0;
}
