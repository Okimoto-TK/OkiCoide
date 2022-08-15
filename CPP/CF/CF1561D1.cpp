#include <cstdio>
int n, mod;
long long f[200005];
long long sum[200005];
int main()
{
	scanf("%d %d", &n, &mod);
	f[1] = 1;
	sum[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		(f[i] += sum[i - 1]) %= mod;
		int l = 2, r;
		for(; l <= i; l = r + 1)
		{
			r = i / (i / l);
			(f[i] += f[i / l] * (r - l + 1) % mod) %= mod;
		}
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
	printf("%lld", f[n]);
	return 0;
}