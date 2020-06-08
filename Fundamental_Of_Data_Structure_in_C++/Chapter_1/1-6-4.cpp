#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 1, 1, 5, 7, 9, 6, 3, 1};
    int times = count(arr, arr + sizeof(arr) / sizeof(int), arr[0]);

    cout << times;
    return 0;
}