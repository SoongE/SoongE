#include <iostream>
using namespace std;

int SumArray(int *arr, int n)
{
    int sum = 0;
    if (n < 0)
        throw n;

    for (int i = 0; i < n; i++)
        sum += arr[i];

    return sum;
}

int main()
{
    int n, size;
    cin >> n >> size;
    int *arr = new int[size];
    for (int i = 0; i < size; arr[i] = i, i++)
        ;

    try
    {
        cout << SumArray(arr, n);
    }
    catch (int except)
    {
        cout << except << " can't be the n.";
    }
}