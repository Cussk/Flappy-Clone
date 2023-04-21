#include "GameScene.h"

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

    //creates a physics body with an edge box shape 
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    //create a node for edge box and center it
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //assign edgeBody as the physics body for node
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    //schedule pipes to spawn at designated frequency depending on the width of the game window
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

    return true;
}

void GameScene::SpawnPipe(float deltaTime)
{
    //calls Spawn Pipe function from Pipe class
    pipe.SpawnPipe(this);
}
