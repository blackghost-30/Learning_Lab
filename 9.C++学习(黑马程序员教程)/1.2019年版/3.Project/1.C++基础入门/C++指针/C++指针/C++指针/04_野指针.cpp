#include <iostream>
using namespace std;

int main4()
{
	// 指针变量p指向内存地址编号为0x1100的空间
	int * p = (int *)0x1100;

	// 访问野指针报错 
	cout << *p << endl;

	system("pause");

	return 0;
}