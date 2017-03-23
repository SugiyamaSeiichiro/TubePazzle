#pragma once
#include "cocos2d.h"
class ResultScene :public cocos2d::Layer 
{
private:
	bool init()override;
	CREATE_FUNC(ResultScene);
public:
	static cocos2d::Scene* createScene();
};