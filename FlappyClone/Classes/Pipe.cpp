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
	//test pipe bitmask against others determining if a collision will occur
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

	//create empty node to house points
	auto pointNode = Node::create();
	//create physics body the size of the gaps between the pipes
	auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP));

	//does not move
	pointBody->setDynamic(false);
	//define which collisions will affect the point node
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	//test point node bitmask against others determining if a collision will occur
	pointBody->setContactTestBitmask(true);

	//sets Physic body on point node
	pointNode->setPhysicsBody(pointBody);
	//positioned in Pipe gap
	pointNode->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe->getContentSize().height / 2) - ((Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP) / 2)));

	//child point nod to layer
	layer->addChild(pointNode);

	//move point node by move speed macro * screen size width, move across screen in negative position x-axis, do not move in y-axis 
	auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));

	//call action
	pointNode->runAction(pointNodeAction);
}

