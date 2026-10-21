#include <iostream>
using namespace std;

int* func()
{
	int* a = new int(10);
	return a;
}

int main3()
{
	int* p = func();

	cout << *p << endl;
	cout << *p << endl;

	// 利用delete释放堆区数据
	delete p;

	//cout << *p << endl; //报错，释放的空间不可访问

	system("pause");

	return 0;
}