#include <iostream>
using namespace std;

// 1. 值传递
void mySwap01(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

// 2. 地址传递
void mySwap02(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// 3. 引用传递
void mySwap03(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main3()
{
	// 定义实参
	int a = 10;
	int b = 20;

	// 值传递不影响实参
	mySwap01(a, b);
	cout << "a:" << a << " b:" << b << endl;

	// 指针传递影响实参
	mySwap02(&a, &b);
	cout << "a:" << a << " b:" << b << endl;

	// 引用传递影响实参
	mySwap03(a, b);
	cout << "a:" << a << " b:" << b << endl;

	system("pause");

	return 0;
}