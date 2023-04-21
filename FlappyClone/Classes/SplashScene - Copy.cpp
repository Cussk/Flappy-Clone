#include "SplashScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    //add layer as child to scene
    scene->addChild(layer);

    return scene;
}

//initiates HelloWorld "Layer", a node with touch functionality
bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}