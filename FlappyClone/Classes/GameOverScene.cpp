#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

//global variable
unsigned int score;
unsigned int highScore;

//scene takes 1 argument for tempScore
Scene* GameOverScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    highScore = score;

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

    Vec2 centerPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    //create sprite for background center in screen
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(centerPosition);

    this->addChild(backgroundSprite);

    //create and position retry button
    auto retryItem = MenuItemImage::create("Retry Button.png", "Retry Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    retryItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3));

    //create and position main menu button
    auto mainMenuItem = MenuItemImage::create("Menu Button.png", "Menu Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
    mainMenuItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4));

    //create menu with 2 buttons
    auto menu = Menu::create(retryItem, mainMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);

    //tiny database for user to store data instances
    UserDefault* def = UserDefault::getInstance();

    //get key value for highscore, if none default to 0
    auto highScore = def->getIntegerForKey("HIGHSCORE", 0);

    //if new score is higher than previously saved highscore update it 
    if (score > highScore)
    {
        highScore = score;

        //set new highscore to key value
        def->setIntegerForKey("HIGHSCORE", highScore);
    }

    //saves key value
    def->flush();

    //string for dynamic score value
    std::string tempScore = StringUtils::format("SCORE: %d", score);

    //create label for score, set font, size, and position
    auto currentScore = Label::createWithTTF(tempScore, "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    currentScore->setPosition(Vec2(visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(currentScore);

    //string for dynamic highscore value
    std::string tempHighScore = StringUtils::format("HIGHSCORE: %d", highScore);

    //create label for highscore, set font, size, color and position
    auto highScoreLabel = Label::createWithTTF(tempHighScore, "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Vec2(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(highScoreLabel);

    return true;
}

//change scene to Main Menu
void GameOverScene::GoToMainMenuScene(cocos2d::Ref* sender)
{
    //create local instance of scene
    auto scene = MainMenu::createScene();

    //change scene with fade transition
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//change scene to Game Scene
void GameOverScene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}