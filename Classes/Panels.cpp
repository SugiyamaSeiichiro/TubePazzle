#include "Panels.h"
#include "Algorithm.h"
#include "DebugDrawNode.h"
#include "Background.h"
#include "LiquidSystem.h"
using namespace cocos2d;
bool Panels::init(std::vector<int> color)
{
	if (!Node::init())
		return false;
	// 物理空間
	initPhysics();
	// 流体空間
	initParticle();
	// 背景
	Background* ground = Background::create(m_world);
	this->addChild(ground, -100);
	Size size = Director::getInstance()->getVisibleSize();
	float r = 50.0f;
	float y = size.height - r * 3;
	std::vector<int> percent = { 40,10,20,30 };
	for (int i = 0; i < Panel_h; i++)
	{
		for (int j = 0; j < Panel_w; j++)
		{
			Random random(percent);
			m_tube[i][j] = Tube::create(m_world);
			m_tube[i][j]->setEntity(
				random.value, Vec2(r + r*2 * j, y - r*2 * i));
			this->addChild(m_tube[i][j]);		
		}
	}
	
	{
		int values[] = { 0, 1, 2, 3 };
		int size = sizeof(values) / sizeof(int);
		shuffle(values, size);
		/*for (int i = 0; i < color.size(); i++)
		{*/
			// 水
			sugiyama::LiquidSystem* liquid = sugiyama::LiquidSystem::create(m_world);
			liquid->setEntity(values[0], color[0]);
			this->addChild(liquid, 10000);
		//}
	}
	{
		int values[] = { 0, 1, 2, 3, 4 };
		int size = sizeof(values) / sizeof(int);
		shuffle(values, size);
		/*for (int i = 0; i < color.size(); i++)
		{*/
			// コップ
			m_cop = Cop::create(m_world);
			m_cop->setEntity(values[0], color[0]);
			this->addChild(m_cop);
		//}
	}
	updateBody();
	scheduleUpdate();
	return true;
}
// 概要：更新処理
void Panels::update(float delta)
{
	m_world->Step(delta, 8, 3);
	updateBody();
	// 液体が溜まったら終了
	if (m_cop->getFinish())
	{
		m_finish = true;
	}
}
void Panels::updateBody()
{
	for (b2Body* body = m_world->GetBodyList();
	body != nullptr; body = body->GetNext())
	{
		Sprite* spr = (Sprite*)body->GetUserData();
		if (spr == nullptr) continue;
		b2Vec2 pos = body->GetPosition();
		spr->setPosition(pos.x*PTM_RATIO, pos.y*PTM_RATIO);
		float rot = body->GetAngle();
		spr->setRotation(-CC_RADIANS_TO_DEGREES(rot));
	}
}
// 概要：乱数を重複しない処理
void Panels::shuffle(int array[], int size)
{
	int i = size;
	while (i > 1) {
		int j = random(0,i-1);
		i--;
		int t = array[i];
		array[i] = array[j];
		array[j] = t;
	}
}
// 概要：タッチ処理
void Panels::touch(cocos2d::Vec2 pos)
{	
	for (int i = 0; i < Panel_h; i++)
	{
		for (int j = 0; j < Panel_w; j++)
		{
			if (m_tube[i][j]->getRect().containsPoint(pos))
			{
				m_tube[i][j]->startRota(0.1f);
				break;
			}
		}
	}
}
// 概要：物理空間初期処理
void Panels::initPhysics()
{
	// ワールド作成
	b2Vec2 gravity(0.0f, -9.8f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	// デバック表示
	DebugDrawNode* debugDraw = DebugDrawNode::create(m_world);
	this->addChild(debugDraw, 1000);
}
// 概要：流体空間の初期処理
void Panels::initParticle()
{
	// 全体のParticleの設定
	b2ParticleSystemDef ParticleSystemDef;
	// 密度
	ParticleSystemDef.density = 1.0f;
	// 半径
	ParticleSystemDef.radius = 3.0f / PTM_RATIO;
	// 構成を覚える
	b2ParticleSystem* ParticleSystem = m_world->CreateParticleSystem(&ParticleSystemDef);
}
// 概要：Panelsの生成
Panels * Panels::create(std::vector<int> color)
{
	Panels* pRet = new(std::nothrow)Panels();
	if (pRet && pRet->init(color))
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
