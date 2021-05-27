#include <stdio.h>
#include <algorithm>
#define N 1007
using namespace std;
int n, m;
int ans;
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
            char buf[2];
            scanf("%1s", buf);
            if(buf[0] == 'F')
            {
                a[i][j] = true;
            }
            L[i][j] = j;
            R[i][j] = j;
            U[i][j] = 1;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 2; j <= m; j++)
        {
            if(a[i][j] && a[i][j - 1])
            {
                L[i][j] = L[i][j - 1];
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = m - 1; j >= 1; j--)
        {
            if(a[i][j] && a[i][j + 1])
            {
                R[i][j] = R[i][j + 1];
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(!a[i][j])
            {
                continue;
            }
            if(i != 1 && a[i][j] && a[i - 1][j])
            {
                U[i][j] = U[i - 1][j] + 1;
                L[i][j] = max(L[i][j], L[i - 1][j]);
                R[i][j] = min(R[i][j], R[i - 1][j]);
            }
            int len = R[i][j] - L[i][j] + 1;
            ans = max(ans, U[i][j] * len);
        }
    }
    printf("%d", 3 * ans);
    return 0;
}
