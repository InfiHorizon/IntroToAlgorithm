#include <iostream>
#include <limits.h>

using namespace std;

#define N 10

// 自顶向下的递归算法
int CUT_ROD(int *p, int n)
{
    if(n == 0)  return 0;

    int q = INT_MIN;
    for(int i = 0; i < n; i++)
    {
        q = max(q, p[i] + CUT_ROD(p, n-i-1));
    }
    return q;
}

// 自顶向下的递归算法+备忘录
int * MEMOIZED_CUT_ROD(int n)
{
    int *r = new int[n+1];  // r[0] indicate n = 0

    for(int i = 0; i < n+1; i++)
    {
        r[i] = INT_MIN;
    }
    return r;
}

int MEMOIZED_CUT_ROD_AUX(int *p, int n, int *r)
{
    if(r[n] >= 0)   return r[n];

    int q = INT_MIN;
    if(n == 0)
    {
        q = 0;
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            q = max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p, n-i-1, r));
        }
    }
    r[n] = q;
    return q;
}

// 自底向上的动态规划算法
int BOTTOM_UP_CUT_ROD(int *p, int n)
{
    int *dp = new int[n+1];
    
    dp[0] = 0;

    for(int i = 1; i <= n; i++)
    {
        int q = INT_MIN;
        for(int j = 0; j < i; j++)
        {
            q = max(q, p[j] + dp[i-j-1]);
        }
        dp[i] = q;
    }
    return dp[n];
}


// 自底向上的动态规划算法 + 重构解
int EXTENDED_BOTTOM_UP_CUT_ROD(int *p, int n, int *s)
{
    int *dp = new int[n+1];
    
    dp[0] = 0;

    for(int i = 1; i <= n; i++)
    {
        int q = INT_MIN;
        for(int j = 0; j < i; j++)
        {
            if(q < p[j] + dp[i-j-1])
            {
                q = p[j] + dp[i-j-1];
                s[i] = j;
            }
        }
        dp[i] = q;
    }
    return dp[n];
}

// 自顶向下的递归算法+备忘录+重构解
int EXTEND_MEMOIZED_CUT_ROD_AUX(int *p, int n, int *r, int *s)
{
    if(r[n] >= 0)   return r[n];

    int q = INT_MIN;
    if(n == 0)
    {
        q = 0;
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            int temp = EXTEND_MEMOIZED_CUT_ROD_AUX(p, n-1-i, r, s);
            if(q < p[i] + temp)
            {
                q = p[i] + temp;
                s[n] = i;
            }
        }
    }
    r[n] = q;
    return q;
}

// 重构解
void PRINT_CUT_ROD_SOLUTION(int *p, int n, int *s)
{
    if(n <= 0) 
    {
        cout << endl;
        return;
    }
    std::cout << s[n] + 1 << " ";
    PRINT_CUT_ROD_SOLUTION(p, n-s[n]-1, s);
}

// 带代价c的自底向上动态规划算法
int BOTTOM_UP_CUT_ROD_WITH_COST(int *p, int n, int c)
{
    int *dp = new int[n+1];
    
    dp[0] = 0;

    for(int i = 1; i <= n; i++)
    {
        int q = p[i-1];
        for(int j = 0; j < i - 1; j++)  // key 2
        {
            q = max(q, p[j] + dp[i-j-1] - c);  // key 3
        }
        dp[i] = q;
    }
    return dp[n];
}


int main()
{
    int p[N] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    int res1 = CUT_ROD(p, N);
    int *r = MEMOIZED_CUT_ROD(N);
    int res2 = MEMOIZED_CUT_ROD_AUX(p, N, r);
    int res3 = BOTTOM_UP_CUT_ROD(p, N);

    int *s = new int[N];
    int res4 = EXTENDED_BOTTOM_UP_CUT_ROD(p, N, s);


    cout << "res1:" << res1 << endl
         << "res2:" << res2 << endl
         << "res3:" << res3 << endl
         << "res4:" << res4 << endl;
    
    PRINT_CUT_ROD_SOLUTION(p, N, s);

    int *r1 = MEMOIZED_CUT_ROD(N);
    int *s1 = new int[N];

    int res5 = EXTEND_MEMOIZED_CUT_ROD_AUX(p, N, r1, s1);
    cout << "res5:" << res5 << endl;
    PRINT_CUT_ROD_SOLUTION(p, N, s1);

    int res6 = BOTTOM_UP_CUT_ROD_WITH_COST(p, N, 5);
    cout << "res6:" << res6 << endl;
}
