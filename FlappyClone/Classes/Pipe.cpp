#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

//function to spawn pipe layer
void Pipe::SpawnPipe(cocos2d::Layer* layer)
{
	CCLOG("SPAWN PIPE");
}

