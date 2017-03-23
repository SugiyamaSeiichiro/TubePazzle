#include "LiquidSystem.h"
#include "Liquid.h"
#include "Tube.h"
#include "AudioEngine.h"
#include "ui\CocosGUI.h"
#define PTM_RATIO 32.0f
using namespace cocos2d;
bool sugiyama::LiquidSystem::init(b2World * world)
{
	if (!Node::init())
		return false;
	m_world = world;
	return true;
}
// 概要：液体の生成
void sugiyama::LiquidSystem::createLiquid()
{
	// 効果音
	experimental::AudioEngine::play2d("liquid.mp3");
	b2ParticleSystem* ParticleSystem = m_world->GetParticleSystemList();
	sugiyama::Liquid* liquid = sugiyama::Liquid::create(ParticleSystem);
	liquid->setEntity(m_pos,m_color);
	this->addChild(liquid);
}

void sugiyama::LiquidSystem::setButton()
{	
	ui::Button* button = ui::Button::create("button.png");
	if (m_color == RED)button->setColor(Color3B::RED);
	else if (m_color == BLUE)button->setColor(Color3B::BLUE);
	else if (m_color == GREEN)button->setColor(Color3B::GREEN);
	else assert(false);
	button->setPosition(m_pos);
	this->addChild(button);
	button->addTouchEventListener(
		[&](Ref * pRef, ui::Widget::TouchEventType type)
	{
		if (m_flag)
			flushLiquid();
		m_flag = false;
	});
}

void sugiyama::LiquidSystem::setEntity(int panel,int color)
{
	m_color = color;
	m_pos = Vec2(panel*100.0f + 50.0f, 750.0f);	
	// 発射管
	Tube* m_tube = Tube::create(m_world);
	m_tube->setEntity(0, m_pos);
	// 固定する
	b2Body* body = m_tube->getBody();
	body->SetType(b2_staticBody);
	body->SetTransform(body->GetPosition(), 0);	
	this->addChild(m_tube);
	// ボタン
	setButton();
}
// 概要：流し始める
void sugiyama::LiquidSystem::flushLiquid()
{	
	DelayTime* time = DelayTime::create(1);
	CallFunc* func = CallFunc::create(
		CC_CALLBACK_0(sugiyama::LiquidSystem::createLiquid, this));
	Sequence*seq = Sequence::create(time, func, nullptr);
	Repeat* re = Repeat::create(seq, 2);
	this->runAction(re);
}
// 概要：LiquidSystemの生成
sugiyama::LiquidSystem * sugiyama::LiquidSystem::create(b2World * world)
{
	LiquidSystem* pRet = new(std::nothrow)LiquidSystem();
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
