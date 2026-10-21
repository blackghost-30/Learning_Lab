#include <iostream>
#include <ctime>		// 时间库
using namespace std;

int main9()
{
	// 0.添加随机数种子,防止每次随机数都相同
	srand((unsigned int)time(NULL));

	// 1.系统生成随机数
	int num = rand() % 100 + 1;		// 生成0 ~ 100的随机数
	//cout << num << endl;

	// 2.玩家进行猜测
	int val = 0;	// 玩家输入数据

	while (1)
	{
		cin >> val;

		// 3.判断玩家的猜测
		// 猜错	提示猜的加过	过大或者过小	重新返回第2步
		if (val > num)
		{
			cout << "猜测过大" << endl;
		}
		else if (val < num)
		{
			cout << "猜测过小" << endl;
		}
		// 猜对	退出游戏
		else
		{
			cout << "恭喜你猜对了" << endl;

			// 猜对了退出循环
			break;
		}
	}

	return 0;
}