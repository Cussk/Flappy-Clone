#pragma once

#include "cocos2d.h"
#include "Pipe.h"
#include "Ball.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    //inline function to set Physics World to local instance of it
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

    bool onContactBegin(cocos2d::PhysicsContact& collision);

    void SpawnPipe(float deltaTime);

    //local instance of physics world
    cocos2d::PhysicsWorld* sceneWorld;

    Pipe pipe;

    Ball* ball;
};