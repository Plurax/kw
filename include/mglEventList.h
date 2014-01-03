


#ifndef H_MGL_EVENT
#define H_MGL_EVENT
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>


class mglEvent
{
	std::wstring Name; // a unique name
	operator()(EventArguments& Args); // functor implementation

}

typedef std::vector<mglEvent*> EvList;


class mglEventList
{
		
}


#endif