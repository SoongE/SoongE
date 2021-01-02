#include <iostream>
using namespace std;

int DivZero(int a, int b, int c)
{
    if (a < 0 && b < 0 && c < 0)
        throw 1;
    else if (a == 0 && b == 0 && c == 0)
        throw 2;
    return a + b * c + b / c;
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    try
    {
        cout << DivZero(a, b, c);
    }
    catch (int except)
    {
        if (except == 1)
        {
            cout << "Can't enter a,b and c less than 0";
            return 0;
        }
        else if (except == 2)
        {
            cout << "Can't enter the 0 to a,b and c";
            return 0;
        }
    }
    return 0;
}