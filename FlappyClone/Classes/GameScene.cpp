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

    //create sprite for background center in screen
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    //create physics edge box for edges of screen
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    //define which collisions will affect the edge
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    //test edge bitmask against others determining if a collsion will occur
    edgeBody->setContactTestBitmask(true);

    //create a node for edge box and center it
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

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
        //create GameOver scene
        auto scene = GameOverScene::createScene();
        //change to game over scene with fade transition
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }

    return true;
}