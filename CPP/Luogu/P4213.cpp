#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#define N23 2000000
int tot;
bool npr[N23 + 5];
int pr[N23 + 5];
int mu[N23 + 5];
int phi[N23 + 5];
int mus[N23 + 5];
long long phis[N23 + 5];
void esv()
{
	mu[1] = 1;
	phi[1] = 1;
	for(int i = 2; i <= N23; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N23; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				mu[i * pr[j]] = 0;
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
			mu[i * pr[j]] = -mu[i];
			phi[i * pr[j]] = phi[i] * (pr[j] - 1);
		}
	}
	for(int i = 1; i <= N23; i++)
	{
		mus[i] = mus[i - 1] + mu[i];
		phis[i] = phis[i - 1] + phi[i];
	}
}
std::unordered_map<long long, std::pair<long long, long long> > hs;
std::pair<long long, long long> dusv(long long n)
{
	//printf("%lld\n", n);
	if(n <= N23)
	{
		return std::make_pair(mus[n], phis[n]);
	}
	if(hs.count(n))
	{
		return hs[n];
	}
	long long ans1 = 1;
	long long ans2;
	//printf("%lld\n", n);
	if(n % 2 == 0)
	{
		ans2 = n / 2 * (n + 1);
	}
	else
	{
		ans2 = (n + 1) / 2 * n;
	}
	//printf("%lld\n", n);
	long long l = 2, r;
	for(; l <= n; l = r + 1)
	{
		r = n / (n / l);
		//if(n == 2008871) printf("%d %d %d\n", l, r, n / l);
		std::pair<long long, long long> re = dusv(n / l);
		ans1 -= (r - l + 1) * 1 * re.first;
		ans2 -= (r - l + 1) * 1 * re.second;
	}
	return hs[n] = std::make_pair(ans1, ans2);
}
int T;
int main()
{
	esv();
	for(scanf("%d", &T); T; T--)
	{
		long long n;
		scanf("%lld", &n);
		auto ans = dusv(n);
		printf("%lld %lld\n", ans.second, ans.first);
	}
	return 0;
}