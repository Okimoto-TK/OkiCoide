#include <cstdio>
#include <algorithm>
#define N 1000005
#define P 998244353
int n, k;
long long a[N], b[N];
long long ans;
struct BIT
{
	private:
		long long t[N];
		int size;
		int lowbit(int x) { return x & (-x); }
	public:
		void build(int s) { size = s; }
		void change(int x, int v)
		{
			for(int i = x; i <= size; i += lowbit(i)) t[i] += v;
		}
		long long query(int x)
		{
			long long r = 0;
			for(int i = x; i > 0; i -= lowbit(i)) r += t[i];
			return r;
		}
} T0, T1;
long long power(long long x, long long k)
{
	long long r = 1;
	while(k != 0)
	{
		if((k & 1) != 0) (r *= x) %= P;
		(x *= x) %= P;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		b[i] = a[i];
	}
	std::sort(b + 1, b + 1 + n);
	int len = std::unique(b + 1, b + 1 + n) - (b + 1);
	a[1] = std::lower_bound(b + 1, b + 1 + len, a[1]) - b;
	T0.build(len);
	T1.build(len);
	T0.change(a[1], 1);
	T1.change(a[1], b[a[1]]);
	ans += b[a[1]];
	for(int i = 2; i <= n; i++)
	{
		a[i] = std::lower_bound(b + 1, b + 1 + len, a[i]) - b;
		T0.change(a[i], 1);
		T1.change(a[i], b[a[i]]);
		if(i - k - 1 >= 1)
		{
			T0.change(a[i - k - 1], -1);
			T1.change(a[i - k - 1], -b[a[i - k - 1]]);
		}
		long long tmp = T0.query(a[i]) * b[a[i]] - T1.query(a[i]);
		((tmp %= P) += P) %= P;
		long long inv = power((long long)i - std::max(1, i - k), P - 2) % P;
		(ans += tmp * inv % P) %= P;
	}
	printf("%lld", ans);
	return 0;
}
