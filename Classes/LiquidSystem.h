#ifndef __LIQUID_SYSTEM_H__
#define __LIQUID_SYSTEM_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
namespace sugiyama
{
	class LiquidSystem : public cocos2d::Node
	{
	private:
		int m_color;	
		b2World* m_world;
		cocos2d::Vec2 m_pos;
		bool m_flag = true;
		bool init(b2World* world);
		void flushLiquid();
		void createLiquid();
		void setButton();
	public:
		void setEntity(int panel,int color);
		static LiquidSystem* create(b2World* world);
	};
}
#endif