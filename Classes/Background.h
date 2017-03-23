#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
class Background : public cocos2d::Node
{
private:
	b2World* m_world;
	b2Body* m_body;
	bool init(b2World* world);
	void addBody(cocos2d::Vec2 v1,cocos2d::Vec2 v2);
public:	
	static Background* create(b2World* world);
};
