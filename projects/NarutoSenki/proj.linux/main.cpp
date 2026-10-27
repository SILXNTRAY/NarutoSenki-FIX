#include "../Classes/AppDelegate.h"
#include "cocos2d.h"
#include "CCEGLView.h"
#include "resource.h"

#include "glfw3.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
	// create the application instance
	AppDelegate app;
	return CCApplication::sharedApplication()->run();
}
