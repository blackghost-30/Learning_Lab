#include <iostream>
using namespace std;

int main3()
{
	// 1.输入分数
	int score = 0;
	cout << "请输入考试分数：" << endl;
	cin >> score;

	// 2.多条件if语句判断
	if (score > 600)
	{
		cout << "我考上了一本大学" << endl;
	}
	else if (score > 500)
	{
		cout << "我考上了二本大学" << endl;
	}
	else if (score > 400)
	{
		cout << "我考上了三本大学" << endl;
	}
	else
	{
		cout << "我未考上本科" << endl;
	}

	system("pause");

	return 0;
}