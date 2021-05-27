#include <stdio.h>
#define N 100007
using namespace std;
int n, m;
int t[N * 4];
bool lazy[N * 4];
void flip(int k, int l, int r)
{
    t[k] = (r - l + 1) - t[k];
    lazy[k] ^= true;
}
void push_up(int k)
{
    t[k] = t[k << 1] + t[k << 1 | 1];
}
int push_down(int k, int l, int r)
{
    int mid = (l + r) >> 1;
    if(lazy[k])
    {
        flip(k << 1, l, mid);
        flip(k << 1 | 1, mid + 1, r);
        lazy[k] ^= true;
    }
    return mid;
}
void change(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        flip(k, l, r);
        return;
    }
    int mid = push_down(k, l, r);
    if(x <= mid)
    {
        change(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        change(k << 1 | 1, mid + 1, r, x, y);
    }
    push_up(k);
}
int query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return t[k];
    }
    int mid = push_down(k, l, r);
    int res = 0;
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
        int c, a, b;
        scanf("%d%d%d", &c, &a, &b);
        if(c == 0)
        {
            change(1, 1, n, a, b);
        }
        else
        {
            printf("%d\n", query(1, 1, n, a, b));
        }
    }
    return 0;
}
