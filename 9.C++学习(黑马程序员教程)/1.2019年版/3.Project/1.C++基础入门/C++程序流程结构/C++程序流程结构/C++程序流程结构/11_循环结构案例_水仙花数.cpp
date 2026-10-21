#include <iostream>
using namespace std;

int main11()
{
	// 1.打印所有三位数字
	int num = 100;

	// 2.从所有三位数字中找到水仙花数
	do
	{
		int a = 0;	// 个位
		int b = 0;	// 十位
		int c = 0;	// 百位

		a = num % 10;			// 获取个位
		b = num / 10 % 10;		// 获取十位
		c = num / 100;			// 获取百位

		// 判断是否为水仙花数
		if (a*a*a + b*b*b +c*c*c)
		{
			cout << num << endl;
		}

		num++;
	} while (num < 1000);

	return 0;
}