#include <stdio.h>
using namespace std;
int n, m, q;
int a[307][307];
int t[107][307][307];
int lowbit(int x)
{
    return x & (-x);
}
void update(int c, int x, int y, int z)
{
    for(int i = x; i <= n; i += lowbit(i))
    {
        for(int j = y; j <= m; j += lowbit(j))
        {
            t[c][i][j] += z;
        }
    }
}
int sum(int c, int x, int y)
{
    int res = 0;
    for(int i = x; i; i -= lowbit(i))
    {
        for(int j = y; j; j -= lowbit(j))
        {
            res += t[c][i][j];
        }
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
            update(a[i][j], i, j, 1);
        }
    }
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1)
        {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            update(a[x][y], x, y, -1);
            a[x][y] = c;
            update(c, x, y, 1);
        }
        else
        {
            int x1, x2, y1, y2, c;
            scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &c);
            printf("%d\n", sum(c, x2, y2) + sum(c, x1 - 1, y1 - 1) - sum(c, x1 - 1, y2) - sum(c, x2, y1 - 1));
        }
    }
    return 0;
}
