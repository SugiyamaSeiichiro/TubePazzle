#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
enum Color{RED,BLUE,GREEN};
namespace sugiyama
{
	class Liquid : public cocos2d::Node
	{
	private:
		b2ParticleSystem* m_ParticleSystem;			
		bool init(b2ParticleSystem* system);
	public:
		void setEntity(cocos2d::Vec2 pos,int color);
		static Liquid* create(b2ParticleSystem* ParticleSystem);
	};
}