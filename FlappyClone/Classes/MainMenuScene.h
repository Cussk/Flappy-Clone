#pragma once

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

private:
    void GoToGameScene(cocos2d::Ref* sender);
    void ExitGame(cocos2d::Ref* sender);
};