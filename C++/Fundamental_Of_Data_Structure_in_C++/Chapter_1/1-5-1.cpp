#include <iostream>
using namespace std;

double HonerFunction(double x, unsigned int size, double *arr)
{
    double res = 0;

    for (unsigned int i = 0; i < size; i++)
        res = res * x + arr[size - i - 1];

    return res;
}

int main()
{
    double arr[] = {1, 2, 3, 4, 5};
    unsigned int size;
    size = sizeof(arr) / sizeof(int);
    cout << HonerFunction(2, size, arr);

    return 0;
}