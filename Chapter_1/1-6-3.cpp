#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    char str[] = "ABCD";
    do
    {
        cout << str << endl;
    } while (next_permutation(str, str + sizeof(str) - 1));

    cout << str << endl;

    return 0;
}