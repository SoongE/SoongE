#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    char str[] = "RHSGAF";
    do
    {
    } while (next_permutation(str, str + sizeof(str) - 1));
    cout << str << endl;
    do
    {
    } while (prev_permutation(str, str + sizeof(str) - 1));
    cout << str;

    return 0;
}