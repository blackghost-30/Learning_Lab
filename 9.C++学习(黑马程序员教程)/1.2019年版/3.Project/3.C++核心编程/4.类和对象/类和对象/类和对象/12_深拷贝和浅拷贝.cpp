#include <iostream>
using namespace std;

class Person
{
public:
    // 无参（默认）构造函数
    Person()
    {
        cout << "无参构造函数!" << endl;
    }

    // 有参构造函数
    Person(int age, int height)
    {
        cout << "有参构造函数!" << endl;

        // 赋值操作
        m_age = age;
        m_height = new int(height);	// 在堆区开辟一个变量并返回地址给到m_height
    }

    // 自己实现拷贝构造函数避免编译器的拷贝构造函数的浅拷贝导致的指针重复释放问题
    Person(const Person& p)
    {
        cout << "拷贝构造函数!" << endl;

        // 如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
        m_age = p.m_age;
        //m_height = p.m_height;			// 编译器提供的浅拷贝
        m_height = new int(*p.m_height);	// 深拷贝重新开辟内存
    }

    // 析构函数
    ~Person()
    {
        cout << "析构函数!" << endl;

        // 释放堆区的地址
        if (m_height != NULL)
        {
            delete m_height;
            m_height = NULL;	// 防止野指针的出现
        }
    }

public:
    int m_age;
    int* m_height;	// 开辟在堆区
};

void test01()
{
    Person p1(18, 180);

    Person p2(p1);

    cout << "p1的年龄： " << p1.m_age << " 身高： " << *p1.m_height << endl;

    cout << "p2的年龄： " << p2.m_age << " 身高： " << *p2.m_height << endl;
}

int main12()
{
    test01();

    system("pause");

    return 0;
}