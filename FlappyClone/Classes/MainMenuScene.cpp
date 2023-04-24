#include "MainMenuScene.h"

#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    //add layer as child to scene
    scene->addChild(layer);

    return scene;
}

//initiates MainMenu "Layer", a node with touch functionality
bool MainMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 centerPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    //create sprite for background center in screen
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(centerPosition);

	this->addChild(backgroundSprite);

    //create sprite for title center on x-axis, y-axis set to top of screen less the height of the sprite
    auto titleSprite = Sprite::create("Title.png");
    titleSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - titleSprite->getContentSize().height / 2));

    this->addChild(titleSprite);

    //image for menu play button, callback to function to change scene
    auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(MainMenu::GoToGameScene, this));
    playItem->setPosition(centerPosition);

    //image for exit button, callback to function to exit application
    auto exitItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MainMenu::ExitGame, this));
    exitItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + exitItem->getContentSize().height / 2));

    //ceate menu 
    auto menu = Menu::create(playItem, exitItem, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);

    return true;
}

//Transitions scene to GameScene
void MainMenu::GoToGameScene(cocos2d::Ref* sender)
{
    //create GameScene
    auto scene = GameScene::createScene();

    //use Director to replace current scene with GameScene using a fade transition
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//Exits game closing application
void MainMenu::ExitGame(cocos2d::Ref* sender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}