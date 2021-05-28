#include <cstdio>
#include <vector>
#define N 300007
#define P 998244353
int n, q;
std::vector<int> g[N];
int dep[N];
int son[N];
int siz[N];
int spr[N];
long long sum[52][N];
long long qPower(long long x, int k)
{
    long long res = 1;
    while(k != 0)
    {
        if(k & 1 == 1) (res *= x) %= P;
        (x *= x) %= P;
        k >>= 1;
    }
    return res;
}
void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    spr[u] = fa;
    for(int i = 1; i <= 50; i++) sum[i][u] = (sum[i][fa] + qPower(dep[u] - 1, i)) % P;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}
int top[N];
void dfs2(int u)
{
    if(son[u] != 0)
    {
        int v = son[u];
        top[v] = top[u];
        dfs2(v);
    }
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(top[v] != 0) continue;
        top[v] = v;
        dfs2(v);
    }
}
long long query(int x, int y, int k)
{
    int fx = top[x];
    int fy = top[y];
    long long res = 0;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            std::swap(fx, fy);
            std::swap(x, y);
        }
        (res += sum[k][x] - sum[k][spr[fx]]) %= P;
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] < dep[y]) std::swap(x, y);
    return (res += sum[k][x] - sum[k][spr[y]]) %= P;
}
int main()
{
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }   
    dfs1(1, 0);
    top[1] = 1;
    dfs2(1);
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        int x, y, k;
        scanf("%d %d %d", &x, &y, &k);
        printf("%lld\n", (query(x, y, k) + P) % P);
    }
    return 0;
}
