#include <stdio.h>
#define MOD 998244353
using namespace std;
int n;
int a[1000007];
int tree[1000007];
int lowbit(int x)
{
    return x & -x;
}
void change(int x)
{
    for(; x <= n; x += lowbit(x))
    {
        tree[x] += 1;
    }
}
int query(int x)
{
    int res = 0;
    for(; x; x -= lowbit(x))
    {
        res += tree[x];
    }
    return res;
}
int cantor()
{
    long long fac = 1;
    long long res = 1;
    for(int i = n; i >= 1; i--)
    {
        res += fac * query(a[i]) % MOD;
        res %= MOD;
        change(a[i]);
        fac *= (n - i + 1);
        fac %= MOD;
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("%d", cantor());
    return 0;
}
