#include <iostream>
using namespace std;

int main3()
{
	// 指针变量p指向内存地址编号为0的空间
	int* p = NULL;

	// 访问空指针会报错 
	// 内存编号0 ~255为系统占用内存，不允许用户访问
	cout << *p << endl;

	system("pause");

	return 0;
}