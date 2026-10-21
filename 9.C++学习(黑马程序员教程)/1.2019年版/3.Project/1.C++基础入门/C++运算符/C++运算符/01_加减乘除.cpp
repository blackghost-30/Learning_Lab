#include <iostream>
using namespace std;

int main1()
{
	// 加减乘除
	int a1 = 10;
	int b1 = 3;

	cout << "a1 + b1 = " << a1 + b1 << endl;
	cout << "a1 - b1 = " << a1 - b1 << endl;
	cout << "a1 * b1 = " << a1 * b1 << endl;
	cout << "a1 / b1 = " << a1 / b1 << endl;	// 结果仍为整数

	// 两个小数可以相除，结果为小数
	double d1 = 0.5;
	double d2 = 0.22;
	cout << "d1 / d2 = " << d1 / d2 << endl;

	system("pause");

	return 0;
}