#pragma once
#include <iostream>
using namespace std;

// 点类:只需要声明不需要实现
class Point
{
	public:
		// 设置x
		void setX(int x);

		// 获取x
		int getX();

		// 设置y
		void setY(int y);

		// 获取y
		int getY();

	private:
		int m_X;	// x坐标
		int m_Y;	// y坐标
};

