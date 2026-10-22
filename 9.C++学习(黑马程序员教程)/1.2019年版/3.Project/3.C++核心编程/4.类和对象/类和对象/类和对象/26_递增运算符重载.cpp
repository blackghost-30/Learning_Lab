#include <iostream>
#include <string>
using namespace std;

// 自己定义的整形数据类
class MyInteger
{
    // 左移运算符的重载友元
    friend ostream& operator<<(ostream& out, MyInteger myint);

public:
    // 无参构造函数
    MyInteger()
    {
        m_Num = 0;
    }

    // 前置++的重载
    // 需要返回引用，否则后续链式运算时就不是对原来的对象操作了
    MyInteger& operator++()
    {
        // 先++
        m_Num++;
        // 再返回
        return *this;
    }

    // 后置++的重载
    // 需要返回值，因为是局部变量不能返回引用
    MyInteger operator++(int)
    {
        // 先返回
        // 记录当前本身的值，然后让本身的值加1，但是返回的是以前的值，达到先返回后++；
        MyInteger temp = *this;
        m_Num++;
        return temp;
    }

private:
    int m_Num;
};

// 左移运算符的重载
ostream& operator<<(ostream& out, MyInteger myint)
{
    out << myint.m_Num;
    return out;
}

// 前置++ 先++ 再返回
void test01()
{
    MyInteger myInt;
    cout << ++myInt << endl;
    cout << myInt << endl;
}

// 后置++ 先返回 再++
void test02()
{
    MyInteger myInt;
    cout << myInt++ << endl;
    cout << myInt << endl;
}

int main26()
{
    test01();
    //test02();

    system("pause");

    return 0;
}