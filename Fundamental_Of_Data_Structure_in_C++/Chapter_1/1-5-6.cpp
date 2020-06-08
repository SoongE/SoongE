#include <iostream>
using namespace std;

int RepeatFactorial(int);
int ReculsiveFactorial(int);

int main()
{
    int n;
    cin >> n;

    cout << "Reculsive " << ReculsiveFactorial(n) << endl;
    cout << "Repeat " << RepeatFactorial(n) << endl;
}

int RepeatFactorial(int n)
{
    int ans = 1;
    for (int i = 1; i < n + 1; i++)
    {
        ans *= i;
    }
    return ans;
}

int ReculsiveFactorial(int n)
{
    if (n <= 1)
        return 1;
    return n * ReculsiveFactorial(n - 1);
}