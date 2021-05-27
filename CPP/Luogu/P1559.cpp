#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int p[32][32];
int q[32][32];
bool va[32];
bool vb[32];
int la[32];
int lb[32];
int up[32];
int lnk[32];
bool dfs(int u)
{
    va[u] = true;
    for(int v = 1; v <= n; v++)
    {
        if(!vb[v])
        {
            if(la[u] + lb[v] == p[u][v])
            {
                vb[v] = true;
                if(!lnk[v] || dfs(lnk[v]))
                {
                    lnk[v] = u;
                    return true;
                }
            }
            else
            {
                up[v] = min(up[v], la[u] + lb[v] - p[u][v]);
            }
        }
    }
    return false;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &p[i][j]);
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &q[i][j]);
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            p[i][j] *= q[j][i];
        }
    }
    for(int i = 1; i <= n; i++)
    {
        la[i] = -(1 << 30);
        lb[i] = 0;
        for(int j = 1; j <= n; j++){ la[i] = max(la[i], p[i][j]); }
        while(true)
        {
            memset(va, 0, sizeof(va));
            memset(vb, 0, sizeof(vb));
            memset(up, 0x3f, sizeof(up));
            if(dfs(i)){ break; }
            int del = 0x3f3f3f3f;
            for(int j = 1; j <= n; j++)
            {
                del = min(del, up[j]);
            }
            for(int j = 1; j <= n; j++)
            {
                if(va[j])
                {
                    la[j] -= del;
                }
                if(vb[j])
                {
                    lb+
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        ans += p[lnk[i]][i];
    }
    printf("%d", ans);
    return 0;
}
