#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n;
char buf[1000007];
struct rnk
{
    int id;
    int f;
    int s;
} rk[1000007];
int sa[1000007];
bool cmp(rnk a, rnk b)
{
    if(a.f == b.f)
    {
        return a.s < b.s;
    }
    else
    {
        return a.f < b.f;
    }
}
int main()
{
    scanf("%s", buf);
    n = strlen(buf);
    for(int i = 1; i <= n; i++)
    {
        sa[i] = buf[i - 1];
    }
    int p = 0;
    int l = 1;
    while(p != n)
    {
        for(int i = 1; i <= n; i++)
        {
            rk[i].id = i;
            if(i + l > n)
            {
                rk[i].f = sa[i];
                rk[i].s = 0;
                continue;
            }
            rk[i].f = sa[i];
            rk[i].s = sa[i + l];
        }
        sort(rk + 1, rk + 1 + n, cmp);
        int l1 = -1;
        int l2 = -1;
        p = 0;
        for(int i = 1; i <= n; i++)
        {
            if(rk[i].f == l1 && rk[i].s == l2)
            {
                sa[rk[i].id] = p;
            }
            else
            {
                sa[rk[i].id] = ++p;
            }
            l1 = rk[i].f;
            l2 = rk[i].s;
        }
        l *= 2;
    }
    p = 0;
    for(int i = 1; i <= n; i++)
    {
        rk[sa[i]].f = ++p;
    }
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", rk[i].f);
    }
    return 0;
}
