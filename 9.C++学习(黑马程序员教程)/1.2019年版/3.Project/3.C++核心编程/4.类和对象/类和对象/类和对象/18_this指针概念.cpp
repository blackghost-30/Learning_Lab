#include <iostream>
#include <string>
using namespace std;

class Person
{
    public:
        Person(int age)
        {
            // 1.当形参和成员变量同名时，可用this指针来区分
            // age = age;		// 将出现乱码
            this->age = age;
        }

        // 要以引用的方式返回，否则返回的是拷贝的数据不是本身
        Person& PersonAddPerson(Person p)
        {
            this->age += p.age;

            // 2.返回对象本身
            return *this;
        }

        int age;
};

void test01()
{
    Person p1(10);
    cout << "p1.age = " << p1.age << endl;

    // 链式编程
    Person p2(10);
    p2.PersonAddPerson(p1).PersonAddPerson(p1).PersonAddPerson(p1);
    cout << "p2.age = " << p2.age << endl;		// 40
}

int main18()
{
    test01();

    system("pause");

    return 0;
}