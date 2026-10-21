#include <iostream>
using namespace std;

int main5()
{
	// 0.定义数组并打印数组
	int arr[9] = { 4, 2, 8, 0, 5, 7, 1, 3, 9 };
	cout << "排序前：" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	// 1.冒泡排序
	// 外层循环次数：数组个数 - 1
	for (int i = 0; i < 9 - 1; i++)
	{
		// 内层循环次数：数组个数 - 循环次数 - 1
		for (int j = 0; j < 9 - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				// 交换元素
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	// 2.打印排序后的数组
	cout << "排序后：" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << arr[i] << " ";
	}

	system("pause");

	return 0;
}