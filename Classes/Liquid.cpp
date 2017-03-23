#include "Liquid.h"
#define PTM_RATIO 32.0f
using namespace cocos2d;
// 概要：初期化
bool sugiyama::Liquid::init(b2ParticleSystem* ParticleSystem)
{
	if (!Node::init())
		return false;
	// 構成を覚える
	m_ParticleSystem = ParticleSystem;	
	return true;
}
// 概要：実体生成
// 引数：位置、色
void sugiyama::Liquid::setEntity(Vec2 pos, int color)
{
	// 形状
	b2PolygonShape shape;
	// 半径
	shape.SetAsBox(15/PTM_RATIO, 40/PTM_RATIO);
	// パーティクル作成
	b2ParticleGroupDef  ParticleGroupDef;
	// 形状
	ParticleGroupDef.shape = &shape;
	// 液体の種類
	ParticleGroupDef.flags = b2_powderParticle;
	// 色	
	if (color == RED)ParticleGroupDef.color.Set(255, 0, 100, 255);
	else if (color == BLUE)ParticleGroupDef.color.Set(0, 255, 100, 255);
	else if (color == GREEN)ParticleGroupDef.color.Set(100, 255, 0, 255);
	else assert(false);
	// 位置
	ParticleGroupDef.position.Set(pos.x / PTM_RATIO, pos.y/ PTM_RATIO);	
	// Particle生成
	m_ParticleSystem->CreateParticleGroup(ParticleGroupDef);
}
// 概要：Liquid生成
sugiyama::Liquid * sugiyama::Liquid::create(b2ParticleSystem* ParticleSystem)
{
	Liquid* pRet = new(std::nothrow)Liquid();
	if (pRet && pRet->init(ParticleSystem))
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
