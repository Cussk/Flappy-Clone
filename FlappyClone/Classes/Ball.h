#pragma once

#include "cocos2d.h"

class Ball
{
public:
    //constructor
    Ball( cocos2d::Layer* layer);

    void Fall(float deltaTime);
    //call sound effect on use
    void Fly();;
    void StopFlying() { isFalling = true; }

    bool getIsFalling() { return isFalling; }
    

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* playerBall;

    bool isFalling;

    
};
