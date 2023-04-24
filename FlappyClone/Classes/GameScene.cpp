#include "GameScene.h"
#include "GameOverScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // create a scene with physics enabled
    auto scene = Scene::createWithPhysics();
    //set physics world to draw debug shapes
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //disable gravity
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    //set physical world to current scene
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    //add layer as child to scene
    scene->addChild(layer);

    return scene;
}

//initiates GameScene "Layer", a node with touch functionality
bool GameScene::init()
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

    //create physics edge box for edges of screen
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    //define which collisions will affect the edge
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    //test edge bitmask against others determining if a collsion will occur
    edgeBody->setContactTestBitmask(true);

    //create a node for edge box and center it
    auto edgeNode = Node::create();
    edgeNode->setPosition(centerPosition);

    //assign edgeBody as the physics body for node
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    //schedule pipes to spawn at designated frequency depending on the width of the game window
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

    //initialize ball class in scene
    ball = new Ball(this);

    //create event listener for collisions
    auto collisionListener = EventListenerPhysicsContact::create();
    //create listener callback to call Contact function
    collisionListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    //dispatches event call to scene
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionListener, this);

    //create single touch event listener
    auto touchListener = EventListenerTouchOneByOne::create();
    //layer will prevent touches from going any layers below it
    touchListener->setSwallowTouches(true);
    //create touch listener callback to call touchbegan function on this scene
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    score = 0;

    //standard library string using cocos string formating to get dynamic score value
    std::string tempScore = StringUtils::format("%d", score);

    //create label for score, set font, size, color and position
    scoreLabel = Label::createWithTTF(tempScore, "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));

    //add as child z-order above everything
    this->addChild(scoreLabel, 10000);

    //calls update function
    this->scheduleUpdate();


    return true;
}


void GameScene::SpawnPipe(float deltaTime)
{
    //calls Spawn Pipe function from Pipe class
    pipe.SpawnPipe(this);
}

//checks when collision occurs returns a bool
bool GameScene::onContactBegin(cocos2d::PhysicsContact& collision)
{
    //get physics body for two shapes
    PhysicsBody* a = collision.getShapeA()->getBody();
    PhysicsBody* b = collision.getShapeB()->getBody();

    //compare if ball collides with pipes or edges as either variable a or b
    if ((BALL_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()) || (BALL_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {

        //CCLOG("SCORE: %i", score);

        //call sound effect
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Hit.mp3");

        //create GameOver scene with score taken from this scene
        auto scene = GameOverScene::createScene(score);
        //change to game over scene with fade transition
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    //compare if ball collides with point node as either variable a or b
    else if ((BALL_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask()) || (BALL_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        //CCLOG("Point Scored");

        //call sound effect
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Point.mp3");

        //increment score
        score++;

        //update score value for label
        std::string tempScore = StringUtils::format("%d", score);

        //set score label to new score
        scoreLabel->setString(tempScore);
    }

    return true;
}

//function called on touch/click of screen
bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //calls Fly function from ball class
    ball->Fly();

    //only allows this function to be called once between each delay time
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::StopFlying), BALL_FLY_DURATION);

    return true;
}

//calls StopFlying function from ball class
void GameScene::StopFlying(float deltaTime)
{
    ball->StopFlying();
}

//calls Fall function from ball class//
void GameScene::update(float deltaTime)
{
    ball->Fall();
}