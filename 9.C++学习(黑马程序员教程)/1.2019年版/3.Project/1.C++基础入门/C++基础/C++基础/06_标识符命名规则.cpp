#include <iostream>
using namespace std;

/*	标识符命名规则
*	1. 标识符不可以是关键字
*	2. 标识符是由字母、数字、下划线构成的
*	3. 标识符第一个字符只能是字母或下划线
*	4. 标识符是区分大小写的
*/
int main6()
{
	// 1.标识符不可以是关键字
	//int int = 10;

	// 2.标识符是由字母、数字、下划线构成的
	int abc = 10;
	int _abc = 20;
	int _123abc = 30;

	// 3.标识符第一个字符只能是字母或下划线
	//int 123abc = 40;

	// 4.标识符是区分大小写的
	int aaa = 100;
	//cout << AAA << endl;

	system("pause");

	return 0;
}