#include <cstdio>
#include <algorithm>
#define N 50000
#define int long long
const int mod = 1000000007;
int tot;
bool npr[N + 5];
int pr[N + 5];
int phi[N + 5];
void esv()
{
	phi[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				phi[i * pr[j]] = pr[j] * phi[i];
				break;
			}
			phi[i * pr[j]] = (pr[j] - 1) * phi[i];
		}
	}
}
int n, m;
signed main()
{
	esv();
	scanf("%lld%lld", &n, &m);
	long long ans = 0;
	int max = std::min(n, m);
	for(int T = 1; T <= max; T++)
	{
		//printf("%d %d %d %d\n", T, phi[T], (n * (n / T) - T * (((n / T) + 1) * (n / T)) / 2), (m * (m / T) - T * ((1 + (m / T)) * (m / T)) / 2));
		ans += 1ll * phi[T] * (n * (n / T) - T * (((n / T) + 1) * (n / T)) / 2) % mod * (m * (m / T) - T * ((1 + (m / T)) * (m / T)) / 2) % mod;
		ans %= mod;
	}
	ans -= (n * (n - 1) / 2) % mod * (m * (m - 1) / 2) % mod;
	ans %= mod;
	ans *= 2;
	if(m >= 3)
	{
		ans += (1ll * m * (m - 1) * (m - 2) / 6) % mod * n;
	}
	if(n >= 3)
	{
		ans += (1ll * n * (n - 1) * (n - 2) / 6) % mod * m;
	}
	printf("%lld", (ans % mod + mod) % mod);
	return 0;
}