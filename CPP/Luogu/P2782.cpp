#include <stdio.h>
#include <algorithm>
using namespace std;
struct rsp
{
    int sth;
    int nth;
};
int n;
rsp a[1000007];
int s[1000007];
bool cmp(rsp a, rsp b)
{
    return a.sth < b.sth;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i].sth, &a[i].nth);
    }
    sort(a + 1, a + 1 + n, cmp);
    s[1] = a[1].nth;
    int len = 1;
    for(int i = 2; i <= n; i++)
    {
        if(a[i].nth > s[len])
        {
            s[++len] = a[i].nth;
        }
        else
        {
            int j = lower_bound(s + 1, s + len + 1, a[i].nth) - s;
            s[j] = a[i].nth;
        }
    }
    printf("%d", len);
    return 0;
}
