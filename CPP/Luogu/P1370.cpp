#include <cstdio>
#include <map>
#define N 100007
#define P 998244353
int n;
int a[N];
long long f[N];
std::map<int, int> last;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++)
    {
        f[i] = (2 * f[i - 1] + 2) % P;
        if(last[a[i]] != 0) (((f[i] -= f[last[a[i]] - 1] + 1) %= P) += P) %= P;
        last[a[i]] = i;
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) (ans += f[i]) %= P;
    printf("%lld", ans);
    return 0;
}
