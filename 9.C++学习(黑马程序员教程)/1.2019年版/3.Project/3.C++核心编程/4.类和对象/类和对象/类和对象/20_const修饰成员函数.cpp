#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person()
    {
        m_A = 0;
        m_B = 0;
    }

    // this指针的本质是一个指针常量（Person * const this），指针的指向不可修改
    // 如果想让指针指向的值也不可以修改，需要声明常函数，相当于const Persion * const this
    void ShowPerson() const
    {
        //const Type* const pointer;
        //this = NULL;		// 不能修改指针的指向，因为是指针常量Person* const this;
        //this->mA = 100;	// 但是this指针指向的对象的数据是可以修改的（前提是该函数不是常函数）

        // const修饰成员函数，表示指针指向的内存空间的数据不能修改，除非mutable修饰的变量
        this->m_B = 100;
    }

    void MyFunc()
    {
        m_A = 10000;
    }

public:
    int m_A;
    mutable int m_B;	// 可修改 可变的
};

// const修饰对象：常对象
void test01()
{
    const Person person;		//常量对象

    cout << person.m_A << endl;
    //person.mA = 100;			// 常对象不能修改成员变量的值,但是可以访问
    person.m_B = 100;			// 但是常对象可以修改mutable修饰成员变量

    // 常对象访问成员函数
    //person.MyFunc();		// 常对象只能调用常函数，因为普通成员函数可以修改属性
}

int main20()
{
    test01();

    system("pause");

    return 0;
}