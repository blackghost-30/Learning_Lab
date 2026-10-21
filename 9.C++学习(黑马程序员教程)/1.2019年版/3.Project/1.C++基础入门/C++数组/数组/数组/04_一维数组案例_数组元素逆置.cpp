#include <iostream>
using namespace std;

int main4()
{
	// 1.创建数组
	int arr[5] = { 1, 2, 3, 4, 5 };
	cout << "数组逆置前：" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << arr[i] << endl;
	}

	// 2. 实现逆置
	int start = 0;
	int end = sizeof(arr) / sizeof(arr[0]) - 1;
	
	while (start < end)
	{
		// 交换元素
		int temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;

		// 更新下标
		start++;
		end--;
	}

	// 3.打印逆置后的数组
	cout << "数组元素逆置后：" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << arr[i] << endl;
	}

	system("pause");

	return 0;
}