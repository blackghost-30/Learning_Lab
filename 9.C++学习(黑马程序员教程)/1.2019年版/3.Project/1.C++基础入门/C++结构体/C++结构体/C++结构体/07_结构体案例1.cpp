#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// 学生结构体
struct Student
{
	// 学生姓名
	string name;

	// 学生分数
	int score;
};

// 老师结构体
struct Teacher
{
	// 老师姓名
	string name;

	// 所带学生数组
	Student sArray[5];
};

// 给老师和学生赋值的函数
void allocateSpace(struct Teacher tArray[], int len)
{
	string tName = "教师";
	string sName = "学生";
	string nameSeed = "ABCDE";

	// 循环赋值
	for (int i = 0; i < len; i++)
	{
		tArray[i].name = tName + nameSeed[i];

		for (int j = 0; j < 5; j++)
		{
			tArray[i].sArray[j].name = sName + nameSeed[j];
			tArray[i].sArray[j].score = rand() % 61 + 40;		// 生成随机分数40 ~ 100
		}
	}
}

// 打印信息的函数
void printTeachers(Teacher tArray[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << tArray[i].name << endl;
		for (int j = 0; j < 5; j++)
		{
			cout << "\t姓名：" << tArray[i].sArray[j].name << " 分数：" << tArray[i].sArray[j].score << endl;
		}
	}
}

int main7()
{
	srand((unsigned int)time(NULL));	//随机数种子 头文件 #include <ctime>

	Teacher tArray[3];	//老师数组

	int len = sizeof(tArray) / sizeof(Teacher);

	allocateSpace(tArray, len);		//创建数据

	printTeachers(tArray, len);		//打印数据

	system("pause");

	return 0;
}