#include <stdio.h>
#include <algorithm>
#include <map>
#include <string.h>
using namespace std;
int n, pool;
int x[1007];
int _x[1007];
int dis[1007][1007];
int bk[1007];
double vl[1007];
double dn[1007];
double sum[1007];
double f[1007][1007][2];
bool cmp(int a, int b)
{
    return a < b;
}
map<int, int> mp;
int main()
{
    scanf("%d%d", &n, &x[0]);
    _x[0] = x[0];
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &x[i]);
        _x[i] = x[i];
    }
    sort(_x, _x + 1 + n, cmp);
    for(int i = 0; i <= n; i++)
    {
        if(mp[_x[i]] == 0)
        {
            mp[_x[i]] = ++pool;
            bk[pool] = _x[i];
        }
    }
    for(int i = 1; i <= pool; i++)
    {
        for(int j = i; j <= pool; j++)
        {
            dis[i][j] = abs(bk[i] - bk[j]);
        }
    }
    for(int i = 1; i <= n; i++)
    {
        int y;
        scanf("%d", &y);
        vl[mp[x[i]]] += double(y) / 1000.0;
    }
    for(int i = 1; i <= n; i++)
    {
        int v;
        scanf("%d", &v);
        dn[mp[x[i]]] += double(v) / 1000.0;
    }
    for(int i = 1; i <= pool; i++)
    {
        sum[i] = sum[i - 1] + dn[i];
    }
    for(int i = 0; i <= pool; i++)
    {
        for(int j = 0; j <= pool; j++)
        {
            f[i][j][0] = double(-(1ll << 62));
            f[i][j][1] = f[i][j][0];
        }
    }
    f[mp[x[0]]][mp[x[0]]][0] = vl[mp[x[0]]];
    f[mp[x[0]]][mp[x[0]]][1] = vl[mp[x[0]]];
    for(int i = mp[x[0]] - 1; i >= 1; i--)
    {
        f[i][mp[x[0]]][0] = f[i + 1][mp[x[0]]][0] + (vl[i] - dis[i][i + 1] * (sum[pool] - (sum[mp[x[0]]] - sum[i])));
    }
    for(int i = mp[x[0]] + 1; i <= pool; i++)
    {
        f[mp[x[0]]][i][1] = f[mp[x[0]]][i - 1][1] + (vl[i] - dis[i - 1][i] * (sum[pool] - (sum[i - 1] - sum[mp[x[0]] - 1])));
    }
    for(int i = mp[x[0]] - 1; i >= 1; i--)
    {
        for(int j = mp[x[0]] + 1; j <= pool; j++)
        {
            f[i][j][0] = max((f[i + 1][j][0] + (vl[i] - dis[i][i + 1] * (sum[pool] - (sum[j] - sum[i])))), (f[i + 1][j][1] + (vl[i] - dis[i][j] * (sum[pool] - (sum[j] - sum[i])))));
            f[i][j][1] = max((f[i][j - 1][0] + (vl[j] - dis[i][j] * (sum[pool] - (sum[j - 1] - sum[i - 1])))), (f[i][j - 1][1] + (vl[j] - dis[j - 1][j] * (sum[pool] - (sum[j - 1] - sum[i - 1])))));
        }
    }
    printf("%.3lf", double(max(f[1][pool][0], f[1][pool][1])) );
    return 0;
}
