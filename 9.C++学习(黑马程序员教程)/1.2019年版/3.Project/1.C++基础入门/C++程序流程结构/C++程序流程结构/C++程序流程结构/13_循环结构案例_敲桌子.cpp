#include <iostream>
using namespace std;

int main13()
{
	// 1,先输出1~100数字
	for (int i = 1; i <= 100; i++)
	{
		// 2.判断是否是7的倍数，或者个位数是7，或者十位数是7
		if (i % 7 ==0 || i % 10 == 7 || i / 10 == 7)
		{
			cout << "敲桌子" << endl;
		}
		else
		{
			cout << i << endl;
		}
	}

	return 0;
}