#include <iostream>

using namespace std;

int fib(int n)
{
    if(n == 0)  return 0;
    if(n == 1)  return 1;
    
    int n1 = 0, n2 = 1, c;
    for(int i = 2; i <= n; i++)
    {
        c = n1 + n2;
        n1 = n2;
        n2 = c;
    }
    return c;
}

int main()
{
    cout << fib(10) << endl;
}
