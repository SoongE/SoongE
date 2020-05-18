#include <iostream>
#include <math.h>

using namespace std;

void Comb(int n)
{
    int number = pow(2, n);
    int *arr = new int[number];
    for (int i = 0; i < number; i++)
        arr[i] = i;
    for (int i = 0; i < number; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            int k = arr[i] >> j; //비트 연산자
            if (k & 1)
                cout << "true ";
            else
                cout << "false ";
        }
        cout << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    try
    {
        Comb(n);
        if (n <= 0)
            throw 1;
    }
    catch (int e)
    {
        cout << "A negative quantity can't be enterd.";
    }
    return 0;
}
