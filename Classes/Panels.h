#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Tube.h"
#include "Cop.h"
#include <vector>
const int Panel_h = 6;
const int Panel_w = 5;
class Panels :public cocos2d::Node
{
private:
	bool m_finish = false;
	Cop* m_cop;
	int m_count;
	b2World* m_world;	
	Tube* m_tube[Panel_h][Panel_w];	
	bool init(std::vector<int> color);
	void update(float delta);
	void updateBody();
	void shuffle(int array[], int size);
	void initPhysics();
	void initParticle();	
public:
	bool getFinish() { return m_finish; }
	void touch(cocos2d::Vec2 pos);
	static Panels* create(std::vector<int> color);
};