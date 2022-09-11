#include <cstdio>
#include <algorithm>
const int mod = 1e9;
int n, m, pool;
int map[15][15];
int set[200];
inline int id(int i, int j)
{
	if(map[i][j] == 0)
	{
		map[i][j] = ++pool;
		set[pool] = pool;
	}
	return map[i][j];
}
char s[15];
int a[15][15];
long long kir[200][200];
int find(int x)
{
	if(set[x] == x) return x;
	return set[x] = find(set[x]);
}
void add_edge(int u, int v)
{
	if(find(u) != find(v))
	{
		set[find(u)] = find(v);
	}
	kir[u][v]--;
	kir[u][u]++;
}
long long det()
{
	int f = 1;
	for(int i = 1; i < pool; i++)
	{
		for(int j = i + 1; j < pool; j++)
		{
			while(kir[i][i])
			{
				long long d = kir[j][i] / kir[i][i];
				for(int k = i; k < pool; k++)
				{
					kir[j][k] = (kir[j][k] - kir[i][k] * d % mod) % mod; 
				}
				std::swap(kir[i], kir[j]);
				f *= -1;
			}
			std::swap(kir[i], kir[j]);
			f *= -1;
		}
	}
	long long ans = 1;
	for(int i = 1; i < pool; i++)
	{
		ans = ans * kir[i][i] % mod;
	}
	return ans * f;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		for(int j = 1; j <= m; j++)
		{
			if(s[j] == '.')
			{
				id(i, j);
				a[i][j] = 1;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(a[i][j] == 0) continue;
			if(j < m && a[i][j + 1] != 0) add_edge(id(i, j), id(i, j + 1));
			if(j > 1 && a[i][j - 1] != 0) add_edge(id(i, j), id(i, j - 1));
			if(i > 1 && a[i - 1][j] != 0) add_edge(id(i, j), id(i - 1, j));
			if(i < n && a[i + 1][j] != 0) add_edge(id(i, j), id(i + 1, j));
		}
	}
	int x = find(1);
	for(int i = 2; i <= pool; i++)
	{
		if(x != find(i))
		{
			printf("0");
			return 0;
		}
	}
	printf("%lld", (det() + mod) % mod);
	return 0;
}