#include <cstdio>
int tot;
bool npr[100005];
int pr[100005];
long long f[100005];
void esv()
{
	f[1] = 1;
	for(int i = 2; i <= 100000; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			f[i] = f[i - 1];
		}
		for(int j = 1; j <= tot && i * pr[j] <= 100000; j++)
		{
			npr[i * pr[j]] = true;
			f[i * pr[j]] = f[i] + f[pr[j]];
			if(i % pr[j] == 0)
			{
				break;
			}
		}
	}
}
int T;
int main()
{
	esv();
	for(scanf("%d", &T); T; T--)
	{
		int m;
		scanf("%d", &m);
		long long ans = 0;
		bool even = false;
		for(int i = 1; i <= m; i++)
		{
			int p, q;
			scanf("%d%d", &p, &q);
			if(p == 1) continue;
			if(p == 2)
			{
				even = true;
			}
			ans += f[p] * q;
		}
		printf("%lld\n", ans + (even ? 0 : 1));
	}
}