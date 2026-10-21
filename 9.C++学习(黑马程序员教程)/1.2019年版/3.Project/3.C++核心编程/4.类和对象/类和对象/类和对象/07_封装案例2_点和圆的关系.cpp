#include <iostream>
#include "point.h"
#include "circle.h"
using namespace std;

// 判断点和圆的关系
void isInCircle(Circle& c, Point& p)
{
	// 计算两点之间距离的平方
	int distance =
		(c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) +
		(c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());

	// 计算半径的平方
	int rDistance = c.getR() * c.getR();

	// 判断关系
	if (distance == rDistance)
	{
		cout << "点在圆上" << endl;
	}
	else if (distance > rDistance)
	{
		cout << "点在圆外" << endl;
	}
	else
	{
		cout << "点在圆内" << endl;
	}
}

int main7()
{
	// 创建圆
	Circle c;
	c.setR(10);				// 设置半径
	Point center;
	center.setX(10);		// 设置圆心x坐标
	center.setY(0);			// 设置圆心y坐标
	c.setCenter(center);	// 设置圆心坐标

	// 创建点
	Point p;
	p.setX(10);
	p.setY(10);

	// 判断关系
	isInCircle(c, p);

	system("pause");

	return 0;
}