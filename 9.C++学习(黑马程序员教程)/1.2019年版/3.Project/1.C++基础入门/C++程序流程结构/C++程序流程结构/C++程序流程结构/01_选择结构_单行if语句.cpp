#include <iostream>
using namespace std;

int main1()
{
	// 选择结构-单行if语句
	// 输入一个分数，如果分数大于600分，视为考上一本大学，并在屏幕上打印

	// 用户输入分数
	int score = 0;
	cout << "请输入一个分数：" << endl;
	cin >> score;
	
	// 打印用户输入的分数
	cout << "您输入的分数为： " << score << endl;

	// if语句判断
	if (score > 600)
	{
		cout << "我考上了一本大学！！！" << endl;
	}

	system("pause");

	return 0;
}