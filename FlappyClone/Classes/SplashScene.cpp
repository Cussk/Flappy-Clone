#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocostudio/SimpleAudioEngine.h"

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

//initiates SplashScene "Layer", a node with touch functionality
bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    //initiate audio effects
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Hit.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Point.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Wing.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/backgroundMusic.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/mainmenuMusic.mp3");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 centerPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    //schedules selector to run once calling function to transition scene to main menu using delay time macro
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);

    //create and center background image
    auto backgroundSprite = Sprite::create("Cuss.png");
    backgroundSprite->setPosition(centerPosition);

    //child sprite to layer
    this->addChild(backgroundSprite);

    return true;
}

//Call to transition to Main Menu Scene
void SplashScene::GoToMainMenuScene(float delta)
{
    //create MainMenu Scene
    auto scene = MainMenu::createScene();

    //call director to replace current scene using transition fade with duration to Main Menu
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
