#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
enum Color{RED,BLUE,GREEN};
class Cop : public cocos2d::Node,b2QueryCallback
{
private:
	cocos2d::Label* m_label;
	bool m_finish;
	int m_count;
	b2World* m_world;
	b2Body* m_body;
	bool init(b2World* world);
	void update(float delta);
	b2PolygonShape createShape(float x,float y,float w,float h);
	void addBody(b2Shape &shape, cocos2d::Sprite* spr = nullptr);
	bool ReportFixture(b2Fixture* fixture)override { return false; }
	bool ReportParticle(const b2ParticleSystem* particleSystem, int32 index)override;
public:	
	bool getFinish()const { return m_finish; }
	void setEntity(int panel,int color);	
	static Cop* create(b2World* world);
};