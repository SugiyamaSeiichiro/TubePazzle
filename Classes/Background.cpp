#include "Background.h"
#define PTM_RATIO 32.0f
using namespace cocos2d;
// 概要：初期化
bool Background::init(b2World* world)
{
	if (!Node::init())
		return false;
	// worldを覚える
	m_world = world;
	// 画面サイズ取得
	Size size = Director::getInstance()->getVisibleSize();	
	// 背景画像
	Sprite* spr = Sprite::create("ground.png");
	spr->setPosition(size.width / 2, size.height / 2);
	this->addChild(spr);
	Vec2 lb(0, 0);			// 左下
	Vec2 rb(size.width, 0);	// 右下
	Vec2 lt(0, size.height);// 左上
	Vec2 rt(size);			// 右上
	addBody(lb, rb);	// 床	
	addBody(lt, rt);	// 天井	
	addBody(lt, lb);	// 左壁	
	addBody(rb, rt);	// 右壁
	return true;
}
// 概要：Bodyの追加
// 引数：繋げたい点2つ
void Background::addBody(Vec2 v1,Vec2 v2)
{
	if (!m_body)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(0, 0);
		m_body = m_world->CreateBody(&bodyDef);
	}
	b2EdgeShape shape;
	b2Vec2 b2v1 = b2Vec2(v1.x / PTM_RATIO, v1.y / PTM_RATIO);
	b2Vec2 b2v2 = b2Vec2(v2.x / PTM_RATIO, v2.y / PTM_RATIO);
	shape.Set(b2v1,b2v2);
	m_body->CreateFixture(&shape, 0);
}
// 概要：背景の生成
Background* Background::create(b2World* world)
{
	Background* pRet = new(std::nothrow)Background();
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
