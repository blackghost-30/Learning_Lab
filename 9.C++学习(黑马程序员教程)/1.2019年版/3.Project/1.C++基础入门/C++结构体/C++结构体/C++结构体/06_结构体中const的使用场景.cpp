#include <iostream>
#include <string>
using namespace std;

// 学生结构体定义
struct student
{
	// 成员列表
	string name;	//姓名
	int age;		//年龄
	int score;		//分数
};

// const使用场景, 这里采用传递指针可以节省空间
void printStudent(const student* stu)		//加const防止函数体中的误操作
{
	//stu->age = 100;		// 操作失败，因为加了const修饰, 即常量指针指向的值不可修改
	cout << "姓名：" << stu->name << " 年龄：" << stu->age << " 分数：" << stu->score << endl;
}

int main6()
{
	student stu = { "张三",18,100 };

	printStudent(&stu);

	system("pause");

	return 0;
}