#include "PlayScene.h"
#include "ResultScene.h"
#include <vector>
#define PTM_RATIO 32.0f
using namespace cocos2d;
// 概要：初期化
bool PlayScene::init()
{
	if (!Layer::init())
		return false;
	std::vector<int> color{ rand() % 3 };
	// パネル
	m_panels = Panels::create(color);
	this->addChild(m_panels);
	// カウントアップ
	m_count = sugiyama::CountUp::create("timer/back.png");
	m_count->setPosition(Vec2(450, 750));
	this->addChild(m_count);
	// タッチ有効化
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	// 更新処理開始
	this->scheduleUpdate();
	return true;
}

void PlayScene::update(float delta)
{
	if (m_panels->getFinish())
	{
		m_count->saveRanking(6);
		auto scene = ResultScene::createScene();
		auto director = Director::getInstance();
		director->replaceScene(scene);
	}
}
// 概要：タッチ開始処理
bool PlayScene::onTouchBegan(Touch * touch, Event * event)
{
	// 物理空間座標に変換
	Vec2 location = touch->getLocation();
	m_panels->touch(location);
	bool hit = m_count->getRect().containsPoint(location);
	if (hit)
	{
		auto scene = PlayScene::createScene();
		auto director = Director::getInstance();
		director->replaceScene(scene);
	}
	return false;
}

void PlayScene::onTouchMoved(Touch * touch, Event * event)
{
	
}

void PlayScene::onTouchEnded(Touch * touch, Event * event)
{	
	
}



// 概要：シーンの生成
Scene * PlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}
