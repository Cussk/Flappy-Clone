#pragma once

#include "cocos2d.h"

class Pipe
{
public:
    //constructor
    Pipe();

    void SpawnPipe(cocos2d::Layer* layer);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

};
