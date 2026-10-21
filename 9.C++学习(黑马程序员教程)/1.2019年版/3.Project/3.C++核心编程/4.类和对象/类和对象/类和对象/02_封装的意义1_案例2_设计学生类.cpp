#include <iostream>
#include <string>
using namespace std;

// 学生类
class Student
{
public:
    // 行为：设置名字、设置ID、显示学生
    void setName(string name)
    {
        m_name = name;
    }

    void setID(int id)
    {
        m_id = id;
    }

    void showStudent()
    {
        cout << "name:" << m_name << " ID:" << m_id << endl;
    }

public:
    // 属性：名字、ID
    string m_name;
    int m_id;
};

int main2()
{
    // 1.实例化一个对象
    Student stu;

    // 2.设置名字和学号并展示,也可以直接赋值设置名字和学号
    stu.setName("德玛西亚");
    stu.setID(250);
    stu.showStudent();

    system("pause");

    return 0;
}