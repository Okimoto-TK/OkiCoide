#include <cstdio>
#include <algorithm>
#define N 100000
const long long mod = (1ll << 31) - 1;
const long long omod = 1ll << 31;
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
int f[N + 5];
int g[N + 5];
struct Sigma
{
	long long v;
	int id;
} ord[N + 5];
bool cmp1(Sigma x, Sigma y)
{
	return x.v < y.v;
}
long long sigma[N + 5];
inline void qmod(long long & x)
{
	x &= mod;
}
inline long long getMod(long long x)
{
	return x & mod;
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k & 1)
		{
			r *= x;
		}
		x *= x;
		k >>= 1;
	}
	return r;
}
inline void esv()
{
	mu[1] = 1;
	sigma[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
			sigma[i] = 1 + i;
			g[i] = 1;
			f[i] = 1;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				mu[i * pr[j]] = 0;
				if(g[i] == 1) sigma[i * pr[j]] = (power(pr[j], f[i] + 2) - 1) / (pr[j] - 1);
				qmod(sigma[i * pr[j]] = g[i] * sigma[power(pr[j], f[i] + 1)]);
				g[i * pr[j]] = g[i];
				f[i * pr[j]] = f[i] + 1;
				break;
			}
			mu[i * pr[j]] = -mu[i];
			qmod(sigma[i * pr[j]] = sigma[i] * (1 + pr[j]));
			g[i * pr[j]] = sigma[i];
			f[i * pr[j]] = 1;
		}
	}
	for(int i = 1; i <=	N; i++)
	{
		//printf("%d %lld\n", i, sigma[i]);
		ord[i].v = sigma[i];
		ord[i].id = i;
	}
	std::sort(ord + 1, ord + 1 + N, cmp1);
}
int q;
struct query
{
	int n, m, a;
	int id;
} que[20005];
bool cmp2(query x, query y)
{
	return x.a < y.a;
}
long long bit[N * 2];
inline int lowbit(int x)
{
	return x & (-x);
}
void modify(int x, long long v)
{
	for(int i = x; i <= N; i += lowbit(i))
	{
		qmod(bit[i] += v);
	}
}
long long query(int x)
{
	long long re = 0;
	for(int i = x; i > 0; i -= lowbit(i))
	{
		qmod(re += bit[i]);
	}
	return re;
}
long long ans[20005];
int main()
{
	esv();
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		scanf("%d%d%d", &que[i].n, &que[i].m, &que[i].a);
		que[i].id = i;
	}
	std::sort(que + 1, que + 1 + q, cmp2);
	int ptr = 1;
	for(int i = 1; i <= q; i++)
	{
		while(ptr <= N && ord[ptr].v <= que[i].a)
		{
			for(int j = ord[ptr].id; j <= N; j += ord[ptr].id)
			{
				modify(j, ord[ptr].v * mu[j / ord[ptr].id]);
			}
			ptr++;
		}
		int l = 1, r;
		int max = std::min(que[i].n, que[i].m);
		for(; l <= max; l = r + 1)
		{
			r = std::min(que[i].n / (que[i].n / l), que[i].m / (que[i].m / l));
			qmod(ans[que[i].id] += getMod((query(r) - query(l - 1)) * (que[i].n / l)) * (que[i].m / l));
		}
	}
	for(int i = 1; i <= q; i++)
	{
		printf("%lld\n", (ans[i] % omod + omod) % omod);
	}
	return 0;
}
