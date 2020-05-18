#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int arr[10] = {5, 7, 9, 3, 10, 51, 79, 21, 37, 70};
    sort(arr, arr + 10);
    for (int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
}