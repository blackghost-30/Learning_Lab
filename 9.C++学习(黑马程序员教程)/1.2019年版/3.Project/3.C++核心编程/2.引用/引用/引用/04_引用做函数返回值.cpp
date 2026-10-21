#include <iostream>
using namespace std;

// 返回局部变量引用
int& test01()
{
	int a = 10;		// 局部变量
	return a;
}

// 返回静态变量引用
int& test02()
{
	static int a = 20;
	return a;
}

int main4()
{
	// 不能返回局部变量的引用
	int& ref = test01();
	cout << "ref = " << ref << endl;	// 第一次编译器会做保留
	cout << "ref = " << ref << endl;	// 后续无法保证正确性

	// 如果函数做左值，那么必须返回引用
	int& ref2 = test02();
	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	test02() = 1000;		// 函数的返回作为左值

	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	system("pause");

	return 0;
}