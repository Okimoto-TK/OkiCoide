#include <stdio.h>
#define N 100007
using namespace std;
int n, m;
long long t[N * 4];
void push_up(int k)
{
    t[k] = t[k << 1] + t[k << 1 | 1];
}
void change(int k, int l, int r, int x, int v)
{
    if(l == r)
    {
        t[k] += v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, v);
    }
    else
    {
        change(k << 1 | 1, mid + 1, r, x, v);
    }
    push_up(k);
}
long long query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return t[k];
    }
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid)
    {
        res += query(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        res += query(k << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        char opt[2];
        int a, b;
        scanf("%s%d%d", opt, &a, &b);
        if(opt[0] == 'x')
        {
            change(1, 1, n, a, b);
        }
        else
        {
            printf("%lld\n", query(1, 1, n, a, b));
        }
    }
    return 0;
}
