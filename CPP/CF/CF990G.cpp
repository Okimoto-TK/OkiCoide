#include <cstdio>
#include <cmath>
#include <vector>
#define N 200000
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
int tot;
void esv()
{
	mu[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				mu[i * pr[j]] = 0;
				break;
			} 
			mu[i * pr[j]] = -mu[i];
		}
	}
}
int n;
int a[N + 5];
bool b[N + 5];
long long f[N + 5];
long long ans[N + 5];
std::vector<int> lyr[N + 5];
std::vector<int> vec[N + 5];
int dfs(int u)
{
	b[u] = false;
	int siz = 1;
	for(auto v : vec[u])
	{
		if(b[v])
		{
			siz += dfs(v);
		}
	}
	return siz;
}
int main()
{
	esv();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		int max = sqrt(a[i]);
		for(int j = 1; j <= max; j++)
		{
			if(a[i] % j == 0)
			{
				lyr[j].push_back(i);
				if(a[i] / j != j)
				{
					lyr[a[i] / j].push_back(i);
				}
			}
		}
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	for(int d = 1; d <= N; d++)
	{
		for(auto i : lyr[d])
		{
			b[i] = true;
		}
		int cnt = 0;
		for(auto i : lyr[d])
		{
			if(b[i]) cnt = dfs(i);
			f[d] += 1ll * (cnt) * (cnt + 1) / 2;
			cnt = 0;
		}
	}
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= N / i; j++)
		{
		//	if(f[i * j] != 0) printf("%d %d %d\n", i, mu[j], f[i * j]);
			ans[i] += mu[j] * f[i * j];
		}
	}
	for(int i = 1; i <= N; i++)
	{
		if(ans[i] == 0) continue;
		printf("%d %lld\n", i, ans[i]);
	}
	return 0;
}
