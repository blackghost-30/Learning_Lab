#include <iostream>
#include <string>
using namespace std;

class Person
{
    // 全局函数做友元
    friend ostream& operator<<(ostream& out, Person& p);

public:
    // 有参构造函数
    Person(int a, int b)
    {
        this->m_A = a;
        this->m_B = b;
    }

    // 成员函数实现不了p << cout,不是我们想要的效果
    //void operator<<(Person& p)
    //{
    //
    //}

private:
    int m_A;
    int m_B;
};

// 全局函数实现左移重载
// ostream对象只能有一个，故用引用方式
// 以ostream类型返回是为了后面的链式编程
ostream& operator<<(ostream& out, Person& p)
{
    out << "a:" << p.m_A << " b:" << p.m_B;
    return out;
}

void test()
{
    Person p1(10, 20);

    cout << p1 << "hello world" << endl;	//链式编程
}

int main25()
{
    test();

    system("pause");

    return 0;
}