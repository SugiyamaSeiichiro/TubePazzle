#include "Cop.h"
#include "Tube.h"
#include "Algorithm.h"
#pragma execution_character_set("utf-8")
#define PTM_RATIO 32.0f
using namespace cocos2d;
bool Cop::init(b2World * world)
{
	if(!Node::init())
	return false;
	m_world = world;
	m_finish = false;	
	return true;
}

void Cop::update(float delta)
{	
	if (m_finish)return;
	Sprite* spr = (Sprite*)m_body->GetUserData();
	if (spr == nullptr) return;
	m_count = 0;
	int count = m_world->GetParticleSystemList()->GetParticleCount();
	if (count == 0)return;
	Rect rect = spr->getBoundingBox();
	b2AABB aabb;
	aabb.lowerBound.x = rect.origin.x / PTM_RATIO;
	aabb.lowerBound.y = rect.origin.y / PTM_RATIO;
	aabb.upperBound.x = (rect.origin.x + rect.size.width) / PTM_RATIO;
	aabb.upperBound.y = (rect.origin.y + rect.size.height) / PTM_RATIO;
	m_world->QueryAABB(this, aabb);	
	if (m_count >= count / 3)
	{
		m_finish = true;
	}
	float percent = (float)m_count / (count / 3)*100.0f;
	char s[128];
	sprintf(s, "%.1f％", percent);	
	m_label->setString(s);	
}

b2PolygonShape Cop::createShape(float x, float y, float w, float h)
{
	b2PolygonShape shape;
	b2Vec2 points[]=
	{
		{(x+w)/PTM_RATIO,(y+h)/PTM_RATIO},
		{(x+w)/PTM_RATIO,(y-h)/PTM_RATIO},
		{(x-w)/PTM_RATIO,(y-h)/PTM_RATIO},
		{(x-w)/PTM_RATIO,(y+h)/PTM_RATIO},
	};
	int count = sizeof(points) / sizeof(b2Vec2);
	shape.Set(points, count);
	return shape;
}

void Cop::addBody(b2Shape & shape, cocos2d::Sprite * spr)
{
	if (m_body==nullptr)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.userData = spr;
		m_body = m_world->CreateBody(&bodyDef);
	}
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	m_body->CreateFixture(&fixtureDef);
}

bool Cop::ReportParticle(const b2ParticleSystem * particleSystem, int32 index)
{	
	/*const b2ParticleColor* colorBuffer = particleSystem->GetColorBuffer();

	b2ParticleColor color = colorBuffer[index];

	b2ParticleColor member;

	if (color == member)
	{

	}*/
	
	m_count++;
	return true;
}

void Cop::setEntity(int panel, int color)
{	
	Sprite* spr = Sprite::create("cop.png");
	if (color == RED)spr->setColor(Color3B::RED);
	else if (color == BLUE)spr->setColor(Color3B::BLUE);
	else if (color == GREEN)spr->setColor(Color3B::GREEN);
	else assert(false);
	this->addChild(spr);
	m_label = Label::create("0.0％", "Arial", 30);
	m_label->setPosition(spr->getContentSize() / 2);
	spr->addChild(m_label);
	float r = spr->getContentSize().width / 2;
	float x = r*0.9f; float y = 0.0f;
	float w = r*0.1f; float h = r;
	b2PolygonShape shape;
	shape = createShape(x, y, w, h);
	addBody(shape,spr);
	shape = createShape(-x, y, w, h);
	addBody(shape);
	Exchange(x, y);
	Exchange(w, h);
	shape = createShape(x, -y, w, h);
	addBody(shape);
	b2Vec2 pos = b2Vec2(panel*100.0f + 50.0f, 50.0f);	
	pos.x /= PTM_RATIO; pos.y /= PTM_RATIO;
	m_body->SetTransform(pos, 0);
	scheduleUpdate();
}

Cop * Cop::create(b2World * world)
{
	Cop* pRet = new(std::nothrow)Cop();
	if (pRet && pRet->init(world))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
