#include <stdio.h>
#define N 140000
using namespace std;
struct node
{
    int cov;
    bool v;
    node()
    {
        v = false;
        cov = -1;
    }
} t[4 * N];
int m;
bool ans[N];
void cover(int k, int v)
{
    t[k].cov = v;
    t[k].v = 0;
}
void flip(int k)
{
    t[k].v ^= 1;
}
int push_down(int k, int l, int r)
{
    int mid = (l + r) >> 1;
    if(t[k].cov != -1)
    {
        cover(k << 1, t[k].cov);
        cover(k << 1 | 1, t[k].cov);
        t[k].cov = -1;
    }
    if(t[k].v)
    {
        flip(k << 1);
        flip(k << 1 | 1);
        t[k].v = false;
    }
    return mid;
}
void modify(int k, int l, int r, int x, int y, int v)
{
    if(x <= l && r <= y)
    {
        cover(k, v);
        return;
    }
    int mid = push_down(k, l, r);
    if(x <= mid)
    {
        modify(k << 1, l, mid, x, y, v);
    }
    if(y > mid)
    {
        modify(k << 1 | 1, mid + 1, r, x, y, v);
    }
}
void change(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        flip(k);
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
}
void push(int k, int l, int r)
{
    if(l == r)
    {
        ans[l] = t[k].v ^ (t[k].cov == -1 ? 0 : t[k].cov);
        return;
    }
    int mid = push_down(k, l, r);
    push(k << 1, l, mid);
    push(k << 1 | 1, mid + 1, r);
}
int main()
{
    char opt[2], br1[2], br2[2];
    int a, b;
    while(scanf("%1s", opt) != EOF)
    {
        scanf("%1s%d,%d%1s", br1, &a, &b, br2);
        a++;
        b++;
        a *= 2;
        b *= 2;
        if(br1[0] == '(')
        {
            a++;
        }
        if(br2[0] == ')')
        {
            b--;
        }
        if(opt[0] == 'U')
        {
            modify(1, 1, N, a, b, 1);
        }
        else if(opt[0] == 'I')
        {
            modify(1, 1, N, 1, a - 1, 0);
            modify(1, 1, N, b + 1, N, 0);
        }
        else if(opt[0] == 'D')
        {
            modify(1, 1, N, a, b, 0);
        }
        else if(opt[0] == 'C')
        {
            change(1, 1, N, 1, N);
            modify(1, 1, N, 1, a - 1, 0);
            modify(1, 1, N, b + 1, N, 0);
        }
        else
        {
            change(1, 1, N, a, b);
        }
    }
    push(1, 1, N);
    bool f = false;
    bool g = true;
    for(int i = 2; i <= N; i++)
    {
        if(!f && ans[i])
        {
            f = true;
            g = false;
            if(i & 1)
            {
                printf("(%d,", (i - 1) / 2 - 1);
            }
            else
            {
                printf("[%d,", i / 2 - 1);
            }
        }
        else if(f && !ans[i])
        {
            f = false;
            if(i & 1)
            {
                printf("%d] ", (i - 1) / 2 - 1);
            }
            else
            {
                printf("%d) ", i / 2 - 1);
            }
        }
    }
    if(g)
    {
        printf("empty set");
    }
    return 0;
}
