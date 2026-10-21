#include <iostream>
using namespace std;

// 1.构造函数分类
// 按照参数分类分为 有参和无参构造   无参又称为默认构造函数
// 按照类型分类分为 普通构造和拷贝构造

class Person
{
public:
    // 无参（默认）构造函数
    Person()
    {
        cout << "无参构造函数的调用!" << endl;
    }

    // 有参构造函数
    Person(int a)
    {
        age = a;
        cout << "有参构造函数的调用!" << endl;
    }

    // 拷贝构造函数（即把另外一个对象的属性和行为都拷贝给自己）
    Person(const Person& p)
    {
        age = p.age;
        cout << "拷贝构造函数的调用!" << endl;
    }

    // 析构函数
    ~Person()
    {
        cout << "析构函数的调用!" << endl;
    }

public:
    int age;
};

// 2.构造函数的调用
// 调用无参构造函数
void test01()
{
    Person p;		// 调用无参构造函数

    // 注意1：调用无参构造函数不能加括号，如果加了编译器认为这是一个函数声明
    //Person p();
}

// 调用有参的构造函数
void test02()
{
    // 2.1  括号法
    Person p1(10);	// 调用有参构造函数
    Person p2(p1);	// 调用拷贝构造函数

    // 2.2 显式法
    Person p3 = Person(10);
    Person p4 = Person(p3);

    //Person(10)单独写就是匿名对象，当前行结束之后，马上析构

    // 注意2：不能利用拷贝构造函数初始化匿名对象，编译器认为是对象声明
    //Person (p4);

    // 2.3 隐式转换法
    Person p5 = 10;		// Person p5 = Person(10); 
    Person p6 = p5;		// Person p6 = Person(p5); 
}

int main9()
{
    test01();
    //test02();

    system("pause");

    return 0;
}