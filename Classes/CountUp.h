#pragma once
#include "cocos2d.h"
#include <vector>
namespace sugiyama
{
	class CountUp :public cocos2d::Node
	{
	private:
		cocos2d::Sprite* m_spr;
		// 秒数保存変数
		float m_count = 0.0f;
		// 数字の表示
		cocos2d::Label* m_label;
		// 初期化
		bool init(const std::string &filename);
		// 更新処理
		void update(float delta);
		// 0を除いて小さい順に整列
		void sort(std::vector<float> &a);
	public:
		cocos2d::Rect getRect()const { return m_spr->getBoundingBox(); }
		void setPosition(cocos2d::Vec2 pos) { m_spr->setPosition(pos); }
		// ランキングに保存
		void saveRanking(const int n);
		// 現在時間取得
		float getCount()const { return m_count; }
		// CountUpの生成
		static CountUp* create(const std::string &filename);
	};
}