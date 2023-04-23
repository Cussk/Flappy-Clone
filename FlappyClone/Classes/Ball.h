#pragma once

#include "cocos2d.h"

class Ball
{
public:
    //constructor
    Ball( cocos2d::Layer* layer);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* playerBall;
};