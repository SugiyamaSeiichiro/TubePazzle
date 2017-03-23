#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "Panels.h"
#include "CountUp.h"
class PlayScene : public cocos2d::Layer
{
private:
	Panels* m_panels;	
	sugiyama::CountUp* m_count;
	bool init()override;
	void update(float delta);	
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);	
	CREATE_FUNC(PlayScene);
public:
	static cocos2d::Scene* createScene();
};