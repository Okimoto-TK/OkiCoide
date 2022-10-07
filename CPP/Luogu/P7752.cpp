#include <cstdio>
#include <cstring>
#include <bitset>
#include <queue>
#define N 1000000
const int mod = 1e9 + 7;
int n, p, cnt1, cnt2;
long long k;
int top;
int stk[N + 5];
int cnt[N + 5];
int d[N + 5];
std::bitset<N + 5> vis;
int f[N + 5];
std::queue<int> q;
std::queue<int> t;
void init()
{
	d[0] = 1;
	d[1] = k;
	d[2] = 1ll * k * (k - 1) % mod;
	d[3] = 1ll * k * (k - 1) % mod * (k - 2) % mod;
	for(int i = 4; i <= N; i++)
	{
		d[i] = (1ll * (k - 1) * d[i - 2] % mod + 1ll * (k - 2) * d[i - 1] % mod) % mod;
	}
}
void dfs(int s)
{
	/*
	if(vis[u]) return;
	if(cnt[u] == 2)
	{
		vis[u] = true;
		return;
	}
	if(++cnt[u] == 1) cnt1++;
	else cnt2++;
	dfs(f[u]);
	vis[u] = true;
	*/
	q.push(s);
	t.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		if(vis[u]) continue;
		if(cnt[u] == 2)
		{
			vis[u] = true;
			continue;
		}
		if(++cnt[u] == 1) cnt1++;
		else cnt2++;
		q.push(f[u]);
		t.push(f[u]);
	}
	while(!t.empty())
	{
		vis[t.front()] = true;
		t.pop();
	}
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%lld", &n, &k);
	init();
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &f[i]);
	}
	long long ans = 1;
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i])
		{
			cnt1 = 0;
			cnt2 = 0;
			dfs(i);
			(ans *= power(k - 1, cnt1 - cnt2)) %= mod;
			(ans *= 1ll * d[cnt2]) %= mod;
		}
	}
	printf("%lld", ans);
	return 0;
}