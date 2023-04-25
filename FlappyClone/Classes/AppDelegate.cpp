#include "AppDelegate.h"
#include "SplashScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

//called when finishing loading game
bool AppDelegate::applicationDidFinishLaunching()
{
    //get instance of director
    auto director = Director::getInstance();

    //set up game window
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::create("Glo");
        //glview->setFrameSize(480, 320);
        director->setOpenGLView(glview);
    }

    //create instance of scene
    auto scene = SplashScene::createScene();

    //use on scene game will start with only
    director->runWithScene(scene);

    return true;
}

//called when game is out of focus
void AppDelegate::applicationDidEnterBackground()
{

}

//called when game is brought back into focus
void AppDelegate::applicationWillEnterForeground()
{

}
