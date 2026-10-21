#include <iostream>
#include <string>
using namespace std;

class Person
{
    public:
        Person()
        {
            mA = 0;
        }

        // 非静态成员变量占对象空间
        int mA;

        // 静态成员变量不占对象空间（属于类）
        static int mB;

        // 函数也不占对象空间，所有函数共享一个函数实例
        void func()
        {
            cout << "mA:" << this->mA << endl;
        }

        // 静态成员函数也不占对象空间（属于类）
        static void sfunc()
        {

        }
};

int main17()
{
    // 1.空对象也需要占据空间，其空间大小为1个字节
    // 2.这里打印的是4字节，只计算int mA的大小
    cout << sizeof(Person) << endl;

    system("pause");

    return 0;
}