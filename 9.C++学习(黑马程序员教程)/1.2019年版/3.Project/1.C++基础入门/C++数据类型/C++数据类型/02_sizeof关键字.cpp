#include <iostream>
using namespace std;

int main2()
{
	// 整形： short（2）	int（4）	long（4）	long long（8）
	// 可以利用sizeof求出数据类型占用内存大小
	
	short num1 = 10;
	cout << "short占用内存空间为： " << sizeof(short) << endl;

	int num2 = 10;
	cout << "int占用内存空间为： " << sizeof(int) << endl;

	long num3 = 10;
	cout << "long占用内存空间为： " << sizeof(long) << endl;

	long long num4 = 10;
	cout << "long long占用内存空间为： " << sizeof(long long) << endl;

	system("pause");

	return 0;
}