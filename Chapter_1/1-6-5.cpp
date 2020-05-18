#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    fill(arr, arr + sizeof(arr) / sizeof(int), 1);

    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}