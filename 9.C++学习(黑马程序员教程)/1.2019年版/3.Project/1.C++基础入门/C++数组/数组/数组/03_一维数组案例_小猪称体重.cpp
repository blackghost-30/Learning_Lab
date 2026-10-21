#include <iostream>
using namespace std;

int main3()
{
	// 1.创建5只小猪体重的数组
	int arr[5] = { 300, 350, 200, 400, 250 };
	
	// 2.从数组中找出最重的小猪体重
	int max = 0;
	for (int i = 0; i < 5; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}

	// 3.打印最大值
	cout << "最重的小猪体重为：" << max << endl;

	system("pause");

	return 0;
}