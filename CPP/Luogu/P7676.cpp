#include <cstdio>
#include <map>
#include <algorithm>
#define int long long
int n;
struct line
{
	int a, b, c;
	bool operator==(const line & x) const
	{
		return a == x.a && b == x.b && c == x.c;
	}
} l[300005];
bool cmp(line x, line y)
{
	if(x.a == y.a)
	{
		if(x.b == y.b)
		{
			return x.c < y.c;
		}
		return x.b < y.b;
	}
	return x.a < y.a;
}
std::map<std::pair<int, int>, int> bu;
std::map<std::pair<int, int>, bool> vis;
int gcd(int a, int b)
{
	if(b == 0) return a;
	else return gcd(b, a % b);
}
int cnt[300005];
long long sum = 0;
long long ans;
const int mod = 1000000007;
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k & 1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld", &l[i].a, &l[i].b, &l[i].c);
		int g = gcd(gcd(l[i].a, l[i].b), l[i].c);
		int ne1 = 1;
		int ne2 = 1;
		if(1ll * l[i].a * l[i].b < 0) ne1 = -1;
		if(1ll * l[i].a * l[i].c < 0) ne2 = -1;
		l[i].a = std::abs(l[i].a / g);
		l[i].b = std::abs(l[i].b / g) * ne1;
		l[i].c = std::abs(l[i].c / g) * ne2;
	}
	std::sort(l + 1, l + 1 + n, cmp);
	int len = std::unique(l + 1, l + 1 + n) - (l + 1);
	n = len;
	for(int i = 1; i <= n; i++)
	{
		int ne = 1;
		int a = l[i].a, b = l[i].b;
		if((a < 0) ^ (b < 0)) ne = -1;
		a = std::abs(a);
		b = std::abs(b);
		int g = gcd(a, b);
		bu[std::make_pair(ne * a / g, b / g)] += 1;
	}
	for(int i = 1; i <= n; i++)
	{
		int ne = 1;
		int a = l[i].a, b = l[i].b;
		if((a < 0) ^ (b < 0)) ne = -1;
		a = std::abs(a);
		b = std::abs(b);
		int g = gcd(a, b);
		cnt[i] = n - bu[std::make_pair(ne * a / g, b / g)];
		sum += cnt[i];
	}
	sum /= 2;
	for(int i = 1; i <= n; i++)
	{
		(ans += (cnt[i] * (cnt[i] - 1) % mod) * power(2, mod - 2) % mod) %= mod;
	}
	for(int i = 1; i <= n; i++)
	{
		int ne = 1;
		int a = l[i].a, b = l[i].b;
		if((a < 0) ^ (b < 0)) ne = -1;
		a = std::abs(a);
		b = std::abs(b);
		int g = gcd(a, b);
		int x = bu[std::make_pair(ne * a / g, b / g)];
		if(!vis[std::make_pair(ne * a / g, b / g)] && x > 1)
		{
			(ans -= (x * (x - 1) % mod) * power(2, mod - 2) % mod * cnt[i]) %= mod;
			vis[std::make_pair(ne * a / g, b / g)] = true;
		}
	}
	printf("%lld", (ans + mod) * power(3, mod - 2) % mod);
	return 0;
}
