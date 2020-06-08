#include <iostream>
using namespace std;

class MyRectangle
{
private:
    int xLow, yLow, height, width;
    string color;

public:
    MyRectangle(int x = 0, int y = 0, int h = 0, int w = 0, string color = "White")
        : xLow(x), yLow(y), height(h), width(w), color(color) {}
    ~MyRectangle() {}

    int GetHeight()
    {
        return height;
    }
    int GetWidth()
    {
        return width;
    }
    int GetArea()
    {
        return height * width;
    }

    bool operator<(MyRectangle &s)
    {
        if (GetArea() < s.GetArea())
            return true;
        else
            return false;
    }
    friend ostream &operator<<(ostream &os, MyRectangle &r);
    friend istream &operator>>(istream &is, MyRectangle &r);
};
ostream &operator<<(ostream &os, MyRectangle &r)
{
    os << "Position : " << r.xLow << ", " << r.yLow << endl;
    os << "Height : " << r.height << endl;
    os << "Width : " << r.width << endl;
    os << "Color : " << r.color << endl;
    return os;
}
istream &operator>>(istream &is, MyRectangle &r){
    cout << "Changint Position : ";
    is >> r.xLow >> r.yLow;
    cout << "Changing Height : ";
    is >> r.height;
    cout << "Changing Width : ";
    is >> r.width;
    cout << "Changing Color : ";
    is >> r.color;
    return is;
}

int main()
{
    MyRectangle a(1, 2, 3, 4, "White");
    MyRectangle b(5, 6, 7, 8, "Blue");

    cout << "A Rectangle\n" << a << endl;
    cout << "B Rectangle\n" << b << endl;

    cin >> a;
    cout << "Changed A\n" << a << endl;
}