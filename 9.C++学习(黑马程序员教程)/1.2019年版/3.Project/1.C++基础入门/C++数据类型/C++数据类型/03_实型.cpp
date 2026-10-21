#include <iostream>
using namespace std;

int main3()
{
	// 默认情况下输出一个小数只显示6位有效数字
	float f1 = 3.1415926f;
	double d1 = 3.1415926;

	cout << "f1 = " << f1 << endl;
	cout << "d1 = " << d1 << endl;

	// 统计float和double占用的内存空间
	cout << "float  sizeof = " << sizeof(f1) << endl;
	cout << "double sizeof = " << sizeof(d1) << endl;

	// 小数的第二种表示方式：科学计数法
	float f2 = 3e2;						// 3 * 10 ^ 2 
	cout << "f2 = " << f2 << endl;

	float f3 = 3e-2;					// 3 * 0.1 ^ 2
	cout << "f3 = " << f3 << endl;

	system("pause");

	return 0;
}