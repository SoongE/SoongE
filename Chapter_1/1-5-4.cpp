#include <iostream>
using namespace std;

int main()
{
    int x, y, z;
    cin >> x >> y >> z;
    if (x > y)
        swap(x, y);
    if (y > z)
        swap(y, z);
    if (x > y)
        swap(x, y);

    printf("%d %d %d", x, y, z);

    return 0;
}