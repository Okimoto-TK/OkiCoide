#include <stdio.h>
#include <algorithm>
using namespace std;
struct beacon
{
    int a;
    int b;
};
int n;
beacon a[100007];
int f[100007];
bool cmp(beacon x, beacon y)
{
    return x.a < y.a;
}
int lower(int pos)
{
    if(pos <= 0)
    {
        return 0;
    }
    int l = 1;
    int r = n;
    int ans = 0;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(a[mid].a < pos)
        {
            l = mid + 1;
            ans = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    return ans;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].a, &a[i].b);
    }
    sort(a + 1, a + 1 + n, cmp);
    int ans = n;
    for(int i = 1; i <= n; i++)
    {
        int edg = lower(a[i].a - a[i].b);
        f[i] = f[edg] + (i - edg - 1);
        ans = min(ans, f[i] + n - i);
    }
    printf("%d", ans);
    return 0;
}
