#include <iostream>
using namespace std;

int main2()
{
	int a = 10;

	int* p;
	p = &a;		//指针指向数据a的地址

	cout << *p << endl;				//* 解引用

	// 32位系统为4字节、64位系统为8字节
	cout << sizeof(p) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(float*) << endl;
	cout << sizeof(double*) << endl;

	system("pause");

	return 0;
}