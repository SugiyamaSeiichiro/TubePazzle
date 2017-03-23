#include "CountUp.h"
using namespace cocos2d;
// 概要：初期化
bool sugiyama::CountUp::init(const std::string &filename)
{
	if (!Node::init())
		return false;
	// 画像
	m_spr = Sprite::create(filename);
	this->addChild(m_spr);
	// 数字
	m_label = Label::create("0", "Arial", 30);
	m_label->setPosition(m_spr->getContentSize() / 2);
	m_spr->addChild(m_label);
	scheduleUpdate();
	return true;
}
// 概要：更新処理
void sugiyama::CountUp::update(float delta)
{
	// 999秒以上いかない
	if (m_count >= 999)
		return;
	// 時間更新
	m_count += delta;
	// 表示更新
	char s[128];
	sprintf(s, "%.f", m_count);
	m_label->setString(s);
}
// 概要：小さい順に整列
void sugiyama::CountUp::sort(std::vector<float>& a)
{
	int n = a.size() - 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = n; j > i; j--)
		{
			// 前の要素が0以外で小さかったら次へ
			// 後ろの要素が０なら次へ
			if (a[j - 1] < a[j]&&a[j-1]!=0.0f||a[j] == 0.0f)
				continue;
			//if (a[j - 1] > a[j] /*&& a[j] != 0.0f || a[j - 1] == 0.0f*/)			
			float t = a[j];
			a[j] = a[j - 1];
			a[j - 1] = t;				
		}
	}
}
// 概要：時間の保存
// 引数：何位まで保存するか
void sugiyama::CountUp::saveRanking(const int n)
{
	// RANK			今回の順位を保存
	// RANKING%d	今までと今回のタイムを並べ替えて保存
	// COUNT		何位まで表示するかを保存
	UserDefault* userDefault = UserDefault::getInstance();
	// 順位の初期化
	userDefault->setIntegerForKey("RANK", -1);
	// 何位まで表示するか
	userDefault->setIntegerForKey("COUNT", n);
	std::vector<float> a(n+1);
	// 今までのタイム取得
	for (int i = 0; i < n; i++)
	{		
		char s[64];
		sprintf(s, "RANKING%d", i);
		a[i] = userDefault->getFloatForKey(s, 0.0f);
	}
	// 今回のタイムを入れる
	a[n] = m_count;
	// 小さい順に整列
	this->sort(a);
	// 並べ替えた全て保存
	for (int i = 0; i < n+1; i++)
	{	
		// 今回のタイムの順位を保存
		if (m_count == a[i])
			userDefault->setIntegerForKey("RANK", i);
		// 並べ替えた値保存
		char s[64];		
		sprintf(s, "RANKING%d", i);
		userDefault->setFloatForKey(s, a[i]);		
	}
}
// 概要：CountUp生成
sugiyama::CountUp * sugiyama::CountUp::create(const std::string &filename)
{
	CountUp* pRet = new(std::nothrow)CountUp();
	if (pRet && pRet->init(filename))
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
