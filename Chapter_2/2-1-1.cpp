#include <iostream>
using namespace std;

class Rectangle
{
private:
    int xLow, yLow, height, width;

public:
    Rectangle(int x = 0, int y = 0, int h = 0, int w = 0)
        : xLow(x), yLow(y), height(h), width(w) {}
    ~Rectangle() {}

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

    bool operator<(Rectangle &s)
    {
        if (GetArea() < s.GetArea())
            return true;
        else
            return false;
    }
    friend ostream &operator<<(ostream &os, Rectangle &r)
    {
        os << "Position : " << r.xLow << ", " << r.yLow << endl;
        os << "Height : " << r.height << endl;
        os << "Width : " << r.width << endl;
        return os;
    }
};

int main()
{
    Rectangle a(1, 2, 3, 4);
    Rectangle b(5, 6, 7, 8);

    cout << "A Rectangle\n"
         << a << endl;
    cout << "B Rectangle\n"
         << b << endl;

    if (a < b)
        cout << "A is smaller than B";
    else
        cout << "A is bigger than B";
    return 0;
}