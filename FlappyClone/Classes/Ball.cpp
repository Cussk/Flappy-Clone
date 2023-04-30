#include "Ball.h"
#include "Definitions.h"
#include "cocostudio/SimpleAudioEngine.h"

USING_NS_CC;

Ball::Ball(cocos2d::Layer* layer)
{
	
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	
	Vec2 centerPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	//create and center player sprite
	playerBall = Sprite::create("Ball.png");
	playerBall->setPosition(centerPosition);

	//create circle physics body the size of the player
	auto playerBallBody = PhysicsBody::createCircle(playerBall->getContentSize().width / 2);
	//define which collisions will affect the player
	playerBallBody->setCollisionBitmask(BALL_COLLISION_BITMASK);
	//test player bitmask against others determining if a collision will occur
	playerBallBody->setContactTestBitmask(true);


	//assign physics body to player sprite
	playerBall->setPhysicsBody(playerBallBody);

	//child player sprite to layer and set z-index to make sure it is at the top of the layer
	layer->addChild(playerBall, 100);

	isFalling = true;
}

//function to change y-axis position depending on falling or not
void Ball::Fall(float deltaTime)
{

	//decrease height on screen
	if (isFalling == true)
	{
		playerBall->setPositionX(visibleSize.width / 2 + origin.x);
		playerBall->setPositionY(playerBall->getPositionY() + (BALL_FALLING_SPEED * visibleSize.height));
	}
	//increase height on screen
	else
	{
		playerBall->setPositionX(visibleSize.width / 2 + origin.x);
		playerBall->setPositionY(playerBall->getPositionY() - (BALL_FLYING_SPEED * visibleSize.height));
	}
}

void Ball::Fly()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Wing.mp3");

	isFalling = false;
	
}
