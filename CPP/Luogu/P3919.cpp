#include <stdio.h>
using namespace std;
struct node
{
    int vl;
    int lc;
    int rc;
};
int n, m, p, rp;
int rt[1000007];
int num[1000007];
node t[21000007];
void con(int &k, int l, int r)
{
    k = ++p;
    if(l == r)
    {
        t[k].lc = 0;
        t[k].rc = 0;
        t[k].vl = num[l];
        return;
    }
    int mid = (l + r) >> 1;
    con(t[k].lc, l, mid);
    con(t[k].rc, mid + 1, r);
}
int cpy(int k)
{
    t[++p] = t[k];
    return p;
}
void ins(int &k, int l, int r, int x, int v)
{
    k = cpy(k);
    if(l == r)
    {
        t[k].lc = 0;
        t[k].rc = 0;
        t[k].vl = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        ins(t[k].lc, l, mid, x, v);
    }
    else
    {
        ins(t[k].rc, mid + 1, r, x, v);
    }
}
int req(int k, int l, int r, int x)
{
    if(l == r)
    {
        return t[k].vl;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        return req(t[k].lc, l, mid, x);
    }
    else
    {
        return req(t[k].rc, mid + 1, r, x);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &num[i]);
    }
    con(rt[rp++], 1, n);
    for(int i = 0; i < m; ++i)
    {
        int v, opt, loc;
        scanf("%d%d%d", &v, &opt, &loc);
        if(opt == 1)
        {
            int val;
            scanf("%d", &val);
            rt[rp] = rt[v];
            ins(rt[rp], 1, n, loc, val);
            rp++;
        }
        else
        {
            rt[rp] = rt[v];
            printf("%d\n", req(rt[rp], 1, n, loc));
            rp ++;
        }
    }
    return 0;
}
