#include <stdio.h>
#include <algorithm>
#define N 2007
using namespace std;
int n, m, ans1, ans2;
bool a[N][N];
int L[N][N];
int R[N][N];
int U[N][N];
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            int buf;
            scanf("%d", &buf);
            L[i][j] = j;
            R[i][j] = j;
            U[i][j] = 1;
            a[i][j] = buf;
            if((i + j) & 1)
            {
                a[i][j] ^= true;
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 2; j <= m; j++)
        {
            if(a[i][j] == a[i][j - 1])
            {
                L[i][j] = L[i][j - 1];
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = m - 1; j >= 1; j--)
        {
            if(a[i][j] == a[i][j + 1])
            {
                R[i][j] = R[i][j + 1];
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(i == 1)
            {
                continue;
            }
            if(a[i][j] == a[i - 1][j])
            {
                U[i][j] = U[i - 1][j] + 1;
                L[i][j] = max(L[i][j], L[i - 1][j]);
                R[i][j] = min(R[i][j], R[i - 1][j]);
            }
            int len = R[i][j] - L[i][j] + 1;
            ans1 = max(ans1, min(U[i][j], len));
            ans2 = max(ans2, U[i][j] * len);
        }
    }
    printf("%d\n%d", ans1 * ans1, ans2);
    return 0;
}
