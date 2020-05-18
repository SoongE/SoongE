#include <iostream>
using namespace std;

int main()
{
    int x, input;
    int *arr = new int[10];
    cout << "Input the value of array that size is 10" << endl;
    for (int i = 0; i < 10; i++)
    {
        cin >> input;
        arr[i] = input;
    }
    cout << "Enter the number that you want to find." << endl;
    cin >> x;

    for (int i = 0; i < 10; i++)
    {
        if (arr[i] == x)
        {
            cout << i;
            return 0;
        }
    }

    cout << -1;
    return 0;
}