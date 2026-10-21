#include <iostream>
using namespace std;

// 引用使用的场景，通常用来修饰形参
void showValue(const int& v)
{
	//v += 10;		// 不能修改了
	cout << v << endl;
}

int main()
{
	// int& ref = 10;  引用本身需要一个合法的内存空间，10这个常量没有别名，因此这行错误
	// 可以加入const修饰，编译器优化代码为：int temp = 10; const int& ref = temp;
	const int& ref = 10;

	// ref = 100;	// 加入const后不可以修改变量
	cout << ref << endl;

	// 函数中利用常量引用防止误操作修改实参
	int a = 10;
	showValue(a);

	system("pause");

	return 0;
}