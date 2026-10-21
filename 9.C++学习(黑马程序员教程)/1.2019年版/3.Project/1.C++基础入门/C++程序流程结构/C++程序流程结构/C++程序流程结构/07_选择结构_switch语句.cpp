#include <iostream>
using namespace std;

int main7()
{
	//请给电影评分 
	//10 ~ 9   经典   
	// 8 ~ 7   非常好
	// 6 ~ 5   一般
	// 5分以下 烂片

	// 1.输入分数
	int score = 0;
	cout << "请给电影打分" << endl;
	cin >> score;

	// 2.switch判断
	switch (score)
	{
		case 10:
		case 9:
			cout << "经典" << endl;
			break;
		case 8:
			cout << "非常好" << endl;
			break;
		case 7:
		case 6:
			cout << "一般" << endl;
			break;
		default:
			cout << "烂片" << endl;
			break;
	}

	system("pause");

	return 0;
}