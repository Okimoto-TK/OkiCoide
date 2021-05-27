#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#define N 40007
#define M 100007
int n, m, blocksize;
int a[N];
int _a[N];
std::vector<int> g[N];
int euP;
int eu[N << 1];
int in[N];
int out[N];
int dep[N];
int siz[N];
int son[N];
int spr[N];
void dfs1(int u, int fa)
{
    in[u] = ++euP;
    eu[euP] = u;
    int len = g[u].size();
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    spr[u] = fa;
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
    out[u] = ++euP;
    eu[euP] = u;
}
int top[N];
void dfs2(int u)
{
    if(son[u])
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
struct query
{
    int l;
    int r;
    int id;
    int bl;
    bool onLCA;
    query()
    {
        bl = id = l = r = 0;
        onLCA = false;
    }
} q[M];
bool cmp(query a, query b)
{
    if(a.bl == b.bl) return a.r < b.r;
    else return a.bl < b.bl;
}
int cnt[N];
bool swp[N];
int tmp;
int ans[M];
void add(int x) { if(cnt[a[eu[x]]]++ == 0) tmp++; }
void del(int x) { if(--cnt[a[eu[x]]] == 0) tmp--; }
int getLCA(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            std::swap(fx, fy);
            std::swap(x, y);
        }
        x = spr[fx];
        fx = top[x];
    }
    return (dep[x] > dep[y]) ? y : x;
}
int main()
{
    scanf("%d%d", &n, &m);
    blocksize = sqrt(n * 2);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        _a[i] = a[i];
    }
    std::sort(_a + 1, _a + 1 + n);
    int len = std::unique(_a + 1, _a + 1 + n) - (_a + 1);
    for(int i = 1; i <= n; i++)
    {
        a[i] = std::lower_bound(_a + 1, _a + 1 + len, a[i]) - _a;
    }
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    top[1] = 1;
    dfs2(1);
    // for(int i = 1; i <= n << 1; i++) printf("%d ", eu[i]);
    // printf("\n");
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if(in[x] > in[y]) std::swap(x, y);
        if(getLCA(x, y) == x)
        {
            q[i].l = in[x];
            q[i].r = in[y];
            q[i].onLCA = true;
        }
        else
        {
            q[i].l = out[x];
            q[i].r = in[y];
            q[i].onLCA = false;
        }
        q[i].id = i;
        q[i].bl = (q[i].l - 1) / blocksize + 1;
    }
    std::sort(q + 1, q + 1 + m, cmp);
    int l = 1;
    int r = 0;
    for(int i = 1; i <= m; i++)
    {
        int ll = q[i].l;
        int rr = q[i].r;
        //printf("%d %d\n", ll, rr);
        int lca = getLCA(eu[ll], eu[rr]);
        while(l > ll)
        {
            swp[eu[--l]] ^= true;
            if(swp[eu[l]]) add(l);
            else del(l);
        }
        while(l < ll)
        {
            swp[eu[l]] ^= true;
            if(swp[eu[l]]) add(l++);
            else del(l++);
        }
        while(r < rr)
        {
            swp[eu[++r]] ^= true;
            if(swp[eu[r]]) add(r);
            else del(r);
        }
        while(r > rr)
        {
            swp[eu[r]] ^= true;
            if(swp[eu[r]]) add(r--);
            else del(r--);
        }
        if(!q[i].onLCA)
        {
            if(swp[lca])
            {
                if(cnt[a[lca]] == 1) ans[q[i].id] = tmp - 1;
                else ans[q[i].id] = tmp;
            }
            else
            {
                if(cnt[a[lca]] == 0) ans[q[i].id] = tmp + 1;
                else ans[q[i].id] = tmp;
            }
        }
        else
        {
            ans[q[i].id] = tmp;
        }
    }
    for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
