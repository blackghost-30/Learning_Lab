#include <iostream>
#include <string>
using namespace std;

// 声明类
class Building;

// 好基友类
class goodGay
{
public:
	goodGay();
	void visit();

private:
	Building* building;
};

// 房子类
class Building
{
	// 告诉编译器:goodGay类是Building类的好朋友，可以访问到Building类中私有内容
	friend class goodGay;

public:
	Building();

public:
	string m_SittingRoom;	//客厅

private:
	string m_BedRoom;	//卧室
};

// 函数的实现
Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

// 函数的实现
goodGay::goodGay()
{
	building = new Building;
}

// 函数的实现
void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay gg;
	gg.visit();
}

int main22()
{
	test01();

	system("pause");

	return 0;
}