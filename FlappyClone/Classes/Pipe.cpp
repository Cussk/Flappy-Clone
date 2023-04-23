#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

//function to spawn pipe layer
void Pipe::SpawnPipe(cocos2d::Layer* layer)
{
	//CCLOG("SPAWN PIPE");

	//creates sprites for pipes
	auto topPipe = Sprite::create("Pipe.png");
	auto bottomPipe = Sprite::create("Pipe.png");

	//create physics body box around pipe sprites
	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

	//cocos macro returns float between 0 and 1
	auto random = CCRANDOM_0_1();


	//bounds to prevent pipes from spawning outside of visible window
	if (random < LOWER_SCREEN_PIPE_THRESHOLD)
	{
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	}
	else if (random > UPPER_SCREEN_PIPE_THRESHOLD)
	{
		random = UPPER_SCREEN_PIPE_THRESHOLD;
	}

	//sets random y-axis position for top pipe
	auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height / 2);

	//physics body does move
	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	//define which collisions will affect the pipe
	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	//test pipe bitmask against others determining if a collsion will occur
	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setContactTestBitmask(true);

	//sets top and bottom pipes to have physics bodies
	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	//spawns pipe just off screen, depending on screen size
	topPipe->setPosition(Vec2(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));
	//mirrors top pipe position with gap for player to fit through
	bottomPipe->setPosition(Vec2(topPipe->getPositionX(), topPipePosition - (Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));

	//add pipes as childs to layer
	layer->addChild(topPipe);
	layer->addChild(bottomPipe);

	//move pipe sprite by move speed macro * screen size width, move across screen in negative positon x-axis, do not move in y-axis 
	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));
	auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));

	//call the actions
	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);


}

