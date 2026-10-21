#include <iostream>
using namespace std;

int * func(int b)
{
	b = 100;
	int a = 10;
	return &a;
}

int main2()
{
	int* p = func(1);

	cout << *p << endl;		// 第一次能打印，因为编译器做了优化
	cout << *p << endl;		// 第二次就不能打印了，编译器不再做保留

	system("pause");

	return 0;
}