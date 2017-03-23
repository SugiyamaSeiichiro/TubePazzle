#include "Tube.h"
#include "Algorithm.h"
#include "AudioEngine.h"
#define PTM_RATIO 32.0f
using namespace cocos2d;
// 概要：初期化
bool Tube::init(b2World * world)
{
	if (!Node::init())
		return false;
	m_world = world;
	return true;
}
// 概要：body追加
void Tube::addBody(b2Shape &shape)
{
	// Bodyが作られてないなら
	if (!m_body)
	{
		// Bodyの情報
		b2BodyDef bodyDef;
		// 影響を受けないBody
		bodyDef.type = b2_kinematicBody;		
		// 90度ずつのパターン取得
		float32 angle = CC_DEGREES_TO_RADIANS(90.0f*(rand() % 3));
		// 角度
		bodyDef.angle = angle;
		// Body生成
		m_body = m_world->CreateBody(&bodyDef);
	}
	// 材質の情報
	b2FixtureDef fixtureDef;
	// 形状
	fixtureDef.shape = &shape;	
	// Bodyに追加
	m_body->CreateFixture(&fixtureDef);	
}
// 概要：追加fixture作成
void Tube::addShape(Type type)
{
	b2PolygonShape shape;
	if (type == LEFT||type == RIGHT)
	{		
		b2Vec2 points[] = {{ m_p.x, m_p.y },{ m_p.y, m_p.x },
		{ m_p.y, -m_p.x },{ m_p.x, -m_p.y }};
		int count = sizeof(points) / sizeof(b2Vec2);
		if (type == LEFT)
		{
			for (int i = 0; i < count; i++)
				points[i].x *= -1;
		}
		shape.Set(points, count);	
	}
	else if (type == BOTTOM)
	{
		b2Vec2 points[] = {{ m_p.y, -m_p.x },{ m_p.x, -m_p.y },
		{ -m_p.x, -m_p.y },{ -m_p.x, -m_p.x },};
		int count = sizeof(points) / sizeof(b2Vec2);
		shape.Set(points, count);
	}
	else if(type==LEFT_TOP||type==RIGHT_TOP||
		type==LEFT_BOTTOM||type==RIGHT_BOTTOM)
	{
		b2Vec2 points[] = {{ m_p.x, m_p.y },{ m_p.y, m_p.x },{ m_p.x, m_p.x } };
		int count = sizeof(points) / sizeof(b2Vec2);
		if(type == LEFT_TOP)
		{
			for (int i = 0; i < count; i++)
				points[i].x *= -1;
		}		
		else if(type == LEFT_BOTTOM)
		{
			for (int i = 0; i < count; i++)
				points[i] *= -1;
		}
		else if(type == RIGHT_BOTTOM)
		{
			for (int i = 0; i < count; i++)
				points[i].y *= -1;
		}
		shape.Set(points, count);		
	}
	addBody(shape);
}
// 概要：Bodyの作成
b2Body * Tube::createBody(b2Vec2 v, b2BodyType type)
{
	b2BodyDef bodyDef;
	bodyDef.position = v;
	bodyDef.type = type;
	b2Body* body = m_world->CreateBody(&bodyDef);
	return body;
}
// 概要：実体の生成
// 引数：種類、位置
void Tube::setEntity(int type, Vec2 pos)
{
	char s[128];
	sprintf(s, "tube/tube(%d).png", type);
	m_spr = Sprite::create(s);	
	this->addChild(m_spr);
	float r = m_spr->getContentSize().width / 2;
	m_p = b2Vec2(r / 5/PTM_RATIO, r/PTM_RATIO);
	if (type == 0)
	{
		addShape(LEFT);
		addShape(RIGHT);
	}
	else if (type == 1)
	{
		addShape(LEFT_TOP);
		addShape(RIGHT_TOP);
		addShape(LEFT_BOTTOM);
		addShape(RIGHT_BOTTOM);
	}
	else if (type == 2)
	{
		addShape(RIGHT_TOP);
		addShape(RIGHT_BOTTOM);
		addShape(LEFT);
	}
	else if (type == 3)
	{
		addShape(BOTTOM);
		addShape(LEFT);
		addShape(RIGHT_TOP);
	}
	else assert(false);
	m_body->SetUserData(m_spr);
	// 現在角度取得
	const float32 angle = m_body->GetAngle();
	//設定位置をb2Vec2に変換
	const b2Vec2 position = b2Vec2(
		pos.x / PTM_RATIO, pos.y / PTM_RATIO);
	// Bodyに反映
	m_body->SetTransform(position, angle);
	// プロテクト設置
	setProtector();
}
// 概要：回転開始
// 引数：秒数
void Tube::startRota(float duration)
{
	// 回転中ならreturn
	if (numberOfRunningActions() != 0)
		return;
	experimental::AudioEngine::play2d("tube.mp3");
	// 指定された時間で90度回転
	float angle = CC_DEGREES_TO_RADIANS(90.0f / duration);
	m_body->SetAngularVelocity(angle);
	// 回転後の角度
	angle = m_body->GetAngle() + CC_DEGREES_TO_RADIANS(90.0f);
	DelayTime* time = DelayTime::create(duration);
	CallFunc* func = CallFunc::create(CC_CALLBACK_0(Tube::stopRota, this, angle));
	Sequence* seq = Sequence::create(time, func, nullptr);
	this->runAction(seq);
}
// 概要：回転終了
void Tube::stopRota(float32 angle)
{
	m_body->SetAngularVelocity(0);
	// 現在位置取得
	const b2Vec2 position = m_body->GetPosition();
	// Bodyに反映
	m_body->SetTransform(position, angle);
}
// 概要：Paticleがはみ出さないようにする
void Tube::setProtector()
{
	float r = m_spr->getContentSize().width / 2;
	b2Vec2 p = b2Vec2(r / 5 / PTM_RATIO, r*1.8f / PTM_RATIO);
	b2Body* body = createBody(m_body->GetPosition(),b2_staticBody);
	b2PolygonShape shape;
	b2Vec2 points[] = 
	{
		{ p.x, p.y },
		{ p.y, p.y },
		{ p.y, p.x },
		{ p.x, p.x },
	};
	int count = sizeof(points) / sizeof(b2Vec2);
	shape.Set(points, count);
	body->CreateFixture(&shape, 0);
	for (int i = 0; i < count; i++)
		points[i].x *= -1;
	shape.Set(points, count);
	body->CreateFixture(&shape, 0);
	for (int i = 0; i < count; i++)
		points[i].y *= -1;
	shape.Set(points, count);
	body->CreateFixture(&shape, 0);
	for (int i = 0; i < count; i++)
		points[i].x *= -1;
	shape.Set(points, count);
	body->CreateFixture(&shape, 0);
}
// 概要：Tubeの生成
Tube * Tube::create(b2World * world)
{
	Tube* pRet = new(std::nothrow)Tube();
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
