#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <map>
#define N 500007
using namespace std;
int n, m, blocksize, pool;
int in[N];
int _in[N];
map<int, int> mp;
int a[N];
struct query
{
    int l;
    int r;
    int id;
    int bl;
} q[2 * N];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return a.r < b.r;
}
int res;
int val[2 * N];
int cnt[2 * N];
int ans[2 * N];
void add(int x)
{
    --val[cnt[a[x]]];
    ++val[++cnt[a[x]]];
    if(cnt[a[x]] > res)
    {
        res = cnt[a[x]];
    }
}
void del(int x)
{
    --val[cnt[a[x]]];
    ++val[--cnt[a[x]]];
    if(val[res] == 0)
    {
        if(cnt[a[x]] == res - 1)
        {
            res--;
        }
    }
}
int main()
{
    scanf("%d", &n);
    while(n)
    {
        memset(val, 0, sizeof(val));
        memset(cnt, 0, sizeof(cnt));
        mp.clear();
        pool = 0;
        res = 0;
        scanf("%d", &m);
        blocksize = 2 * sqrt(n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &in[i]);
            _in[i] = in[i];
        }
        sort(_in + 1, _in + 1 + n);
        for(int i = 1; i <= n; i++)
        {
            if(mp[_in[i]] == 0)
            {
                mp[_in[i]] = ++pool;
            }
        }
        for(int i = 1; i <= n; i++)
        {
            a[i] = mp[in[i]];
        }
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].id = i;
            q[i].bl = (q[i].l - 1) / blocksize + 1;
        }
        sort(q + 1, q + 1 + m, cmp);
        int l = 1;
        int r = 0;
        val[0] = n;
        for(int i = 1; i <= m; i++)
        {
            int ll = q[i].l;
            int rr = q[i].r;
            while(l > ll)
            {
                add(--l);
            }
            while(r < rr)
            {
                add(++r);
            }
            while(l < ll)
            {
                del(l++);
            }
            while(r > rr)
            {
                del(r--);
            }
            ans[q[i].id] = res;
        }
        for(int i = 1; i <= m; i++)
        {
            printf("%d\n", ans[i]);
        }
        scanf("%d", &n);
    }
    return 0;
}
