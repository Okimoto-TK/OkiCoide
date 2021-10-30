#include <cstdio>
#include <algorithm>
struct Req
{
    int b, e, t;
} r[5005];
int n, h;
bool chs[30005];
bool cmp(Req a, Req b)
{
    if(a.e == b.e) return a.b < b.b;
    return a.e < b.e;
}
int cnt(int b, int e)
{
    int res = 0;
    for(int i = b; i <= e; i++)
    {
        res += chs[i] ? 1 : 0;
    }
    return res;
}
int main()
{
    // freopen("P1250.in", "r", stdin);
    // freopen("P1250.out", "w", stdout);
    scanf("%d%d", &n, &h);
    for(int i = 1; i <= h; i++)
    {
        scanf("%d%d%d", &r[i].b, &r[i].e, &r[i].t);
    }
    std::sort(r + 1, r + 1 + h, cmp);
    int ans = 0;
    for(int i = 1; i <= h; i++)
    {
        int more = r[i].t - cnt(r[i].b, r[i].e);
        for(int j = r[i].e; more > 0 && j >= r[i].b; j--)
        {
            if(!chs[j])
            {
                chs[j] = true;
                more--;
                ans++;
            }
        }
    }
    printf("%d", ans);
    return 0;
}
