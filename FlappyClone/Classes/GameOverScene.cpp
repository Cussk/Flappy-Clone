#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    //add layer as child to scene
    scene->addChild(layer);

    return scene;
}

//initiates GameOverScene "Layer", a node with touch functionality
bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}