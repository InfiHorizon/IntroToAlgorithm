#include <iostream>
#include <limits.h>

using namespace std;

#define N 6

int m[N][N];
int s[N][N];

void MATRIX_CHAIN_ORDER(int *p, int n)
{
    for(int i = 0; i < n; i++)
    {
        m[i][i] = 0;
    }

    for(int l = 2; l <= n; l++)
    {
        for(int i = 0; i < n-l+1; i++)
        {
            int j = i + l - 1;
            
            m[i][j] = INT_MAX;
            for(int k = i; k <= j-1; k++)
            {
                int q = m[i][k] + m[k+1][j] + p[i] * p[k+1] * p[j+1];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void PRINT_OPTIMAL_PARENS(int i, int j)
{
    if(i == j)
    {
        cout << "A" << i;
        return;
    }
    cout << "(";
    PRINT_OPTIMAL_PARENS(i, s[i][j]);
    PRINT_OPTIMAL_PARENS(s[i][j]+1, j);
    cout << ")";
}

int main()
{
    int p[N+1] = {30, 35, 15, 5, 10, 20, 25};
    MATRIX_CHAIN_ORDER(p, N);

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << "res:" << m[0][N-1] << endl;

    PRINT_OPTIMAL_PARENS(0, 5);
}