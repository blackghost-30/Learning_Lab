#include <iostream>
using namespace std;

// 堆区开辟数组
int main()
{
	int* arr = new int[10];

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}

	// 释放数组：delete后加[]
	delete[] arr;

	system("pause");

	return 0;
}