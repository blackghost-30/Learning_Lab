#include <iostream>
#include <string>
using namespace std;

int main()
{
	// 1. 整型的输入
	int a = 0;
	cout << "请给整型变量a赋值： " << endl;
	cin >> a;
	cout << "整型变量a = " << a << endl;

	// 2. 浮点型的输入
	float f = 3.14f;
	cout << "请给浮点型变量f赋值： " << endl;
	cin >> f;
	cout << "整型变量f = " << f << endl;

	// 3. 字符型的输入
	char ch = 'a';
	cout << "请给字符型变量ch赋值： " << endl;
	cin >> ch;
	cout << "整型变量ch = " << ch << endl;

	// 4. 字符串型的输入
	string str = "hello";
	cout << "请给字符串str赋值： " << endl;
	cin >> str;
	cout << "字符串变量str = " << str << endl;

	// 5.布尔类型的输入
	bool flag = 0;
	cout << "请给布尔型变量flag赋值： " << endl;
	cin >> flag;
	cout << "布尔变量flag = " << flag << endl;

	system("pause");

	return 0;
}