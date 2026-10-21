#include <iostream>
using namespace std;

int main1()
{
	// 1.指针的定义
	int a = 10;		//定义整型变量a

	// 指针定义语法： 数据类型 * 变量名 ;
	int* p;

	// 指针变量赋值
	p = &a;					//指针指向变量a的地址
	cout << &a << endl;		//打印数据a的地址
	cout << p << endl;		//打印指针变量p

	// 2.指针的使用
	// 通过*操作解引用, 找到指针变量指向的内存的数据
	cout << "*p = " << *p << endl;

	system("pause");

	return 0;
}