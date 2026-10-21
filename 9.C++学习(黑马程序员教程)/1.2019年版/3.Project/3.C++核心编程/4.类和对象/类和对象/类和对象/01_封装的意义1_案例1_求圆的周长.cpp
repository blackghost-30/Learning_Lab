#include <iostream>
using namespace std;

// 圆周率
const double PI = 3.14;

// 1.封装的意义:将属性和行为作为一个整体，用来表现生活中的事物
// 封装一个圆类，求圆的周长
class Circle
{
    public:		// 访问权限  公共的权限

        // 属性
        int m_r;	//半径

        // 行为:获取到圆的周长
        double calculateZC()
        {
            //2 * pi  * r
            return  2 * PI * m_r;
        }
};

int main1()
{
    // 通过圆类,创建圆的对象,c1就是一个具体的圆
    Circle c1;
    c1.m_r = 10;	//给圆对象的半径 进行赋值操作

    cout << "圆的周长为： " << c1.calculateZC() << endl;

    system("pause");

    return 0;
}