#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <vector>
#define PTM_RATIO 32.0f
// 2つの数値を交換
class Exchange
{
public:	
	Exchange(float &a, float &b) 
	{
		float tmp = a;
		a = b;
		b = tmp;
	}	
};
// パーセント指定して確率を出す
class Random
{
public:
	int value;
	Random(std::vector<int> percent)
	{
		int max = 0;		
		for (int i = 0; i < percent.size(); i++)
			max += percent[i];
		int r = cocos2d::random(0, max);
		int p = 0; int b = 0;
		for (int i = 0; i < percent.size(); i++)
		{
			p += percent[i];
			// 値を入れる
			if (b <= r && r <= p)
			{
				value = i;
				break;
			}
			b += percent[i];
		}
	}
};
// 2つの数値を比較
class Compare
{
public:
	float max;
	float min;
	Compare(float a, float b)
	{
		if (a > b)
			max = a;
		else min = b;
	}
};

class Sort
{
public:
	Sort(std::vector<float> &vector,int n)
	{		
		for (int i = 0; i < n-1; i++)
		{
			for (int j = n-1; j > i; j--)
			{
				if (vector[j - 1] > vector[j])
				{
					Exchange(vector[j], vector[j - 1]);
				}
			}
		}
	}
};