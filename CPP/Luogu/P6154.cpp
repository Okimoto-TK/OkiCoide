#include <cstdio>
#include <vector>
#include <queue>
#define N 100005
#define P 998244353
int n, m;
std::vector<int> g[N];
int idg[N];
int odg[N];
std::queue<int> q;
long long s[N];
long long c[N];
long long power(long long x, long long k)
{
	long long r = 1;
	while(k != 0)
	{
		if(k % 2 == 1) (r *= x) %= P;
		(x *= x) %= P;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		idg[v]++;
		odg[u]++;
	}
	for(int i = 1; i <= n; i++)
	{
		if(idg[i] == 0)
		{
			q.push(i);
			s[i] = 0;
		}
		c[i] = 1;
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		int len = g[u].size();
		for(int i = 0; i < len; i++)
		{
			int v = g[u][i];
			(c[v] += c[u]) %= P;
			(s[v] += s[u] + c[u]) %= P; 
			if(--idg[v] == 0) q.push(v);
		}
	}
	long long sum = 0;
	long long cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		(sum += s[i]) %= P;
		(cnt += c[i]) %= P;
	}
	printf("%lld", sum % P * power(cnt, P - 2) % P);
	return 0;
}
