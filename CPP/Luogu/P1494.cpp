#include <stdio.h>
#include <algorithm>
#include <math.h>
#define MAX 50007
using namespace std;
int n, m, blocksize, tmp;
int a[MAX];
int cnt[MAX];
int ans[MAX][2];
struct query
{
    int l;
    int r;
    int id;
    int bl;
} q[MAX];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return a.r < b.r;
}
int gcd(int a, int b)
{
    if(!b)
    {
        return a;
    }
    return gcd(b, a % b);
}
int main()
{
    scanf("%d%d", &n, &m);
    blocksize = sqrt(n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
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
    for(int i = 1; i <= m; i++)
    {
        int ll = q[i].l;
        int rr = q[i].r;
        while(l > ll)
        {
            l--;
            tmp += cnt[a[l]]++;
        }
        while(l < ll)
        {
            tmp -= cnt[a[l]]-- - 1;
            l++;
        }
        while(r < rr)
        {
            r++;
            tmp += cnt[a[r]]++;
        }
        while(r > rr)
        {
            tmp -= cnt[a[r]]-- - 1;
            r--;
        }
        ans[q[i].id][0] = tmp;
        ans[q[i].id][1] = 1ll * (rr - ll + 1) * (rr - ll) / 2;
    }
    for(int i = 1; i <= m; i++)
    {
        if(ans[i][0] == 0)
        {
            printf("0/1\n");
            continue;
        }
        int div = gcd(ans[i][0], ans[i][1]);
        printf("%d/%d\n", ans[i][0] / div, ans[i][1] / div);
    }
    return 0;
}
