#include <iostream>
#include <string>
using namespace std;

// 空指针访问成员函数
class Person
{
    public:
        void ShowClassName()
        {
            cout << "我是Person类!" << endl;
        }

        void ShowPerson()
        {
            if (this == NULL)
            {
                return;
            }

            // mAge其实是this->aAge
            cout << mAge << endl;
        }

    public:
        int mAge;
};

void test01()
{
    Person* p = NULL;
    p->ShowClassName();		// 空指针，可以调用成员函数
    p->ShowPerson();		// 但是如果成员函数中用到了this指针，就不可以了
}

int main19()
{
    test01();

    system("pause");

    return 0;
}