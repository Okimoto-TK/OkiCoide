#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#define MAX 100007
using namespace std;
struct query
{
    int l;
    int r;
    int gt;
    int id;
    int bl;
} q[MAX];
int n, m, blocksize;
vector <int> vec[MAX];
int a[MAX];
int son[MAX];
int dep[MAX];
int siz[MAX];
int spr[MAX];
int seg[MAX];
int rpr[MAX];
int top[MAX];
int cnt[MAX];
int val[MAX];
int ans[MAX];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return a.r < b.r;
}
void dfs1(int u, int s)
{
    spr[u] = s;
    siz[u] = 1;
    dep[u] = dep[s] + 1;
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i];
        if(v == s)
        {
            continue;
        }
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]])
        {
            son[u] = v;
        }
    }
}
void dfs2(int u)
{
    if(son[u])
    {
        int v = son[u];
        seg[v] = ++seg[0];
        rpr[seg[v]] = v;
        top[v] = top[u];
        dfs2(v);
    }
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i];
        if(top[v])
        {
            continue;
        }
        seg[v] = ++seg[0];
        rpr[seg[v]] = v;
        top[v] = v;
        dfs2(v);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    blocksize = sqrt(n * 2);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs1(1, 0);
    seg[1] = ++seg[0];
    rpr[seg[1]] = 1;
    top[1] = 1;
    dfs2(1);
    for(int i = 1; i <= m; i++)
    {
        int u, k;
        scanf("%d%d", &u, &k);
        q[i].l = seg[u];
        q[i].r = seg[u] + siz[u] - 1;
        q[i].gt = k;
        q[i].id = i;
        q[i].bl = (q[i].l - 1) / blocksize + 1;
    }
    sort(q + 1, q + 1 + m, cmp);
    int l = 1;
    int r = 0;
    for(int i = 1; i <= m; i++)
    {
        int ll = q[i].l;
        int rr = q[i].r;
        while(l > ll)
        {
            cnt[++val[a[rpr[--l]]]]++;
        }
        while(r < rr)
        {
            cnt[++val[a[rpr[++r]]]]++;
        }
        while(r > rr)
        {
            cnt[val[a[rpr[r--]]]--]--;
        }
        while(l < ll)
        {
            cnt[val[a[rpr[l++]]]--]--;
        }
        ans[q[i].id] = cnt[q[i].gt];
    }
    for(int i = 1; i <= m; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
