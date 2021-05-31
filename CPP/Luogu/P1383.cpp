#include <cstdio>
#define N 100007
int n, pool, ver;
struct Node
{
    int lch;
    int rch;
    char val;
    Node()
    {
        lch = rch = 0;
        val = '\0';
    }
} t[4000000];
int build(int l, int r)
{
    int k = ++pool;
    if(l == r) return k;
    int mid = (l + r) >> 1;
    t[k].lch = build(l, mid);
    t[k].rch = build(mid + 1, r);
    return k;
}
int rt[N];
int len[N];
int insert(int _k, int l, int r, int x, char c)
{
    int k = ++pool;
    if(l == r)
    {
        t[k].val = c;
        return k;
    }
    int mid = (l + r) >> 1;
    t[k].lch = t[_k].lch;
    t[k].rch = t[_k].rch;
    if(x <= mid) t[k].lch = insert(t[k].lch, l, mid, x, c);
    else t[k].rch = insert(t[k].rch, mid + 1, r, x, c);
    return k;
}
char query(int k, int l, int r, int x)
{
    if(l == r) return t[k].val;
    int mid = (l + r) >> 1;
    if(x <= mid) return query(t[k].lch, l, mid, x);
    else return query(t[k].rch, mid + 1, r, x);
}
int main()
{
    scanf("%d", &n);
    rt[0] = build(1, N);
    len[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        char opt[2];
        scanf("%s", opt);
        if(opt[0] == 'T')
        {
            char x[2];
            scanf("%s", x);
            ver++;
            len[ver] = len[ver - 1] + 1;
            rt[ver] = insert(rt[ver - 1], 1, N, len[ver], x[0]);
        }
        else if(opt[0] == 'U')
        {
            int x;
            scanf("%d", &x);
            ver++;
            rt[ver] = rt[ver - 1 - x];
            len[ver] = len[ver - 1 - x];
        }
        else
        {
            int x;
            scanf("%d", &x);
            printf("%c\n", query(rt[ver], 1, N, x));
        }
    }
    return 0;
}
