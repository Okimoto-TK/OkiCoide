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
int n, q, blocksize, ans;
int cnt[1000007];
int out[200007];
int a[30007];
query qr[200007];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return a.r < b.r;
}
int main()
{
    scanf("%d", &n);
    blocksize = sqrt(n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    scanf("%d", &q);
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
        out[qr[i].id] = ans;
    }
    for(int i = 1; i <= q; i++)
    {
        printf("%d\n", out[i]);
    }
    return 0;
}
