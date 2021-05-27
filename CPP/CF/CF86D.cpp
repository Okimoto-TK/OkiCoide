#include <stdio.h>
#include <math.h>
#include <algorithm>
#define MAX 200007
using namespace std;
struct query
{
    int l;
    int r;
    int id;
    int bl;
} qr[MAX];
int n, q, blocksize;
int a[MAX];
long long cnt[5 * MAX];
long long ans[MAX];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return (a.bl & 1) ? a.r < b.r : a.r > b.r;
}
int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    blocksize = sqrt(n) * 2;
    for(int i = 1; i <= q; i++)
    {
        scanf("%d%d", &qr[i].l, &qr[i].r);
        qr[i].id = i;
        qr[i].bl = (qr[i].l - 1) / blocksize + 1;
    }
    sort(qr + 1, qr + 1 + q, cmp);
    int l = 1;
    int r = 0;
    long long tmp = 0;
    for(int i = 1; i <= q; i++)
    {
        int ll = qr[i].l;
        int rr = qr[i].r;
        while(l < ll)
        {
            tmp -= (--cnt[a[l]] * 2 + 1) * a[l];
            l++;
        }
        while(r > rr)
        {
            tmp -= (--cnt[a[r]] * 2 + 1) * a[r];
            r--;
        }
        while(l > ll)
        {
            --l;
            tmp += (++cnt[a[l]] * 2 - 1) * a[l];
        }
        while(r < rr)
        {
            ++r;
            tmp += (++cnt[a[r]] * 2 - 1) * a[r];
        }
        ans[qr[i].id] = tmp;
    }
    for(int i = 1; i <= q; i++)
    {
        printf("%I64d\n", ans[i]);
    }
    return 0;
}
