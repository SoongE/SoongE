#include <iostream>
using namespace std;

int main()
{
    for (int n = 2; n < 22; n += 2)
    {
        int *a = new int[n];
        int i = 0, j = n - 1, x;
        cin >> x;
        printf("n : %d || x : %d\n", n, x);

        do
        {
            int k = (i + j) / 2;
            if (a[k] <= x)
                i = k + 1;
            else
                j = k - 1;
            printf("i : %d \t j : %d\n", i, j);
        } while (i <= j);
        delete[] a;
    }
    return 0;
}