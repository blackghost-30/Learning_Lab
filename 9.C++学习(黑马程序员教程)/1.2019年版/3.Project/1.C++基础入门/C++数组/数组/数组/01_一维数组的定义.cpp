#include <iostream>
using namespace std;

int main1()
{
	// 定义方式1:数据类型 数组名[元素个数];
	int score[10];

	// 利用下标赋值
	score[0] = 100;
	score[1] = 99;
	score[2] = 85;

	// 利用下标输出
	cout << score[0] << endl;
	cout << score[1] << endl;
	cout << score[2] << endl;


	// 第二种定义方式:数据类型 数组名[元素个数] =  {值1，值2 ，值3 ...};
	// 如果{}内不足10个数据，剩余数据用0补全
	int score2[10] = { 100, 90,80,70,60,50,40,30,20,10 };

	// 逐个输出
	//cout << score2[0] << endl;
	//cout << score2[1] << endl;

	// 一个一个输出太麻烦，因此可以利用循环进行输出
	for (int i = 0; i < 10; i++)
	{
		cout << score2[i] << endl;
	}

	// 定义方式3:数据类型 数组名[] =  {值1，值2 ，值3 ...};
	int score3[] = { 100,90,80,70,60,50,40,30,20,10 };

	for (int i = 0; i < 10; i++)
	{
		cout << score3[i] << endl;
	}

	system("pause");

	return 0;
}