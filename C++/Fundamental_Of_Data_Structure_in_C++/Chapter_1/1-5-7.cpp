#include <iostream>
using namespace std;

int RepeatFibo(int n);
int ReculsiveFibo(int n);

int main()
{
    int n;
    cin >> n;

    cout << "Reculsive " << ReculsiveFibo(n) << endl;
    cout << "Repeat " << RepeatFibo(n) << endl;

    return 0;
}

int RepeatFibo(int n)
{
    int f0 = 0, f1 = 1, f2;

    if (n == 0 || n == 1)
        return n;
    for (int i = 2; i < n + 1; i++)
    {
        f2 = f0 + f1;
        f0 = f1;
        f1 = f2;
    }

    return f2;
}

int ReculsiveFibo(int n)
{
    if (n == 0 || n == 1)
        return n;
    return ReculsiveFibo(n - 2) + ReculsiveFibo(n - 1);
}