#pragma once

#include "cocos2d.h"
#include "cocostudio/SimpleAudioEngine.h"

class Ball
{
public:
    //constructor
    Ball( cocos2d::Layer* layer);

    void Fall();
    //call sound effect on use
    void Fly() { CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Wing.mp3"); isFalling = false; };
    void StopFlying() { isFalling = true; }

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* playerBall;

    bool isFalling;
};
