#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
int a[107][107];
int sum[107][107];
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            sum[i][j] = sum[i][j - 1] + a[i][j];
        }
    }
    int max_l = min(n, m);
    int ans = 0;
    for(int l = 1; l <= max_l; l++)
    {
        for(int i = 1; i + l - 1 <= n; i++)
        {
            for(int j = 1; j + l - 1 <= m; j++)
            {
                int x = i + l - 1;
                int y = j + l - 1;
                bool sqr = true;
                for(int k = i; k <= x; k++)
                {
                    if(sum[k][y] - sum[k][j - 1] != l)
                    {
                        sqr = false;
                        break;
                    }
                }
                if(sqr)
                {
                    ans = l;
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}
