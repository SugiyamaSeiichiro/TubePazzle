#include "ResultScene.h"
#include "PlayScene.h"
#include "ui\CocosGUI.h"
#pragma execution_character_set("utf-8")
using namespace cocos2d;
bool ResultScene::init()
{
	if (!Layer::init())
		return false;	
	UserDefault* userDefault = UserDefault::getInstance();
	int count = userDefault->getIntegerForKey("COUNT", 0);
	int now = userDefault->getIntegerForKey("RANK", -1);
	std::vector<float> time;
	for (int i = 0; i < count; i++)
	{
		char s[64];
		sprintf(s, "RANKING%d", i);
		time.push_back(userDefault->getFloatForKey(s,0.0f));		
		if (time[i]>0.0f)sprintf(s, "%d位  %.2f秒", i + 1, time[i]);
		else sprintf(s, "%d位  ー.ー秒", i+1);
		Label* label = Label::create(s, "Arial", 30);
		if (now == i)label->setColor(Color3B::RED);
		label->setPosition(250, 600 - 50 * i);
		this->addChild(label);
	}
	if (now == count)
	{
		char s[64];
		sprintf(s, "RANKING%d", now);
		float time = userDefault->getFloatForKey(s, 0.0f);
		sprintf(s, "圏外  %.2f秒", time);
		Label* label = Label::create(s, "Arial", 30);
		label->setColor(Color3B::RED);
		label->setPosition(250, 600 - 50 * count);
		this->addChild(label);
	}
	// 戻るボタン
	ui::Button* button = ui::Button::create("back_button.png");
	button->setPosition(Vec2(250, 600-50 * (count+2)));
	this->addChild(button);
	button->addTouchEventListener(
		[&](Ref * pRef, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED)return;
		auto scene = PlayScene::createScene();
		auto director = Director::getInstance();
		director->replaceScene(scene);
	});
	return true;
}
// 概要：シーンの生成
cocos2d::Scene * ResultScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ResultScene::create();
	scene->addChild(layer);
	return scene;
}
