#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct query
{
    int l;
    int r;
    int id;
    int bl;
};
int n, q, blocksize, cnt[100007], ans;
int obf[100007];
int a[100007];
query qr[100007];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    else
    {
        return a.r < b.r;
    }
}
int main()
{
    scanf("%d%d", &n, &q);
    blocksize = sqrt(n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= q; i++)
    {
        scanf("%d%d", &qr[i].l, &qr[i].r);
        qr[i].id = i;
        qr[i].bl = (qr[i].l - 1) / blocksize + 1;
    }
    sort(qr + 1, qr + 1 + q, cmp);
    int l = 1;
    int r = 0;
    for(int i = 1; i <= q; i++)
    {
        int ll = qr[i].l;
        int rr = qr[i].r;
        while(l < ll)
        {
            if(--cnt[a[l++]] == 0)
            {
                ans--;
            }
        }
        while(l > ll)
        {
            if(++cnt[a[--l]] == 1)
            {
                ans++;
            }
        }
        while(r < rr)
        {
            if(++cnt[a[++r]] == 1)
            {
                ans++;
            }
        }
        while(r > rr)
        {
            if(--cnt[a[r--]] == 0)
            {
                ans--;
            }
        }
        obf[qr[i].id] = (ans == (rr - ll + 1) ? 1 : 0);
    }
    for(int i = 1; i <= q; i++)
    {
        if(obf[i])
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    return 0;
}
