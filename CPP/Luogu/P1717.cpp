#include <cstdio>
#include <queue>
struct Pool
{
    long long f, d;
    Pool()
    {
        f = d = 0;
    }
    Pool(long long x, long long y)
    {
        f = x, d = y;
    }
    bool operator< (const Pool & p) const
    {
        return this -> f < p.f;
    }
};
long long n, h;
long long f[50];
long long d[50];
long long t[50];
int main()
{
    scanf("%lld%lld", &n, &h);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &f[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &d[i]);
    }
    for(int i = 1; i < n; i++)
    {
        scanf("%lld", &t[i]);
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++)
    {
        int _h = h * 12;
        std::priority_queue<Pool> q;
        for(int j = 1; j <= i; j++)
        {
            _h -= t[j - 1];
            q.push(Pool(f[j], d[j]));
        }
        long long tmp = 0;
        while(_h > 0)
        {
            Pool u = q.top();
            q.pop();
            tmp += u.f;
            q.push(Pool(std::max(0ll, u.f - u.d), u.d));
            _h--;
        }
        ans = std::max(ans, tmp);
    }
    printf("%lld", ans);
    return 0;
}
