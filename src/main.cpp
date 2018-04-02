/*
 * main.cpp
 *
 *  Created on: 22.11.2016
 *      Author: chuhlich
 */

#include <iostream>
using namespace std;
#include "kwBase.h"

#include <unistd.h>



int main(int argc, char* argv[]) {
    kwSystem& MainSystem = kwSystem::Inst();
    kwValString configfile = kwValString("Configuration.json");

    if (argc == 2)
    {
      configfile = kwValString(argv[1]);
    }

    MainSystem.init(configfile);

    bool done = false;

    while (!done)
    {
      auto newMess  = make_shared<kwMessage>(1);
      newMess->setMessageText("TestMessage!");
      MainSystem.addMessage(newMess);

      MainSystem.pollTimers();
      MainSystem.processMessages();
      usleep(1000000);
    }

    return 0;
}
