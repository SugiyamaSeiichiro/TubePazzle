#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <vector>
class Tube :public cocos2d::Node 
{
private:
	enum Type
	{
		LEFT,
		RIGHT,
		BOTTOM,
		LEFT_TOP,
		RIGHT_TOP,
		LEFT_BOTTOM,
		RIGHT_BOTTOM,
	};
	b2World* m_world;
	b2Body* m_body;
	b2Vec2 m_p;
	cocos2d::Sprite* m_spr;
	bool init(b2World* world);	
	void addBody(b2Shape &shape);
	void addShape(Type type);
	b2Body* createBody(b2Vec2 v,b2BodyType type);	
	void stopRota(float32 angle);
	void setProtector();
public:
	b2Body* getBody()const { return m_body; }
	void setEntity(int type, cocos2d::Vec2 pos);
	void startRota(float duration);
	cocos2d::Rect getRect() { return m_spr->getBoundingBox(); }
	static Tube* create(b2World* world);
};
