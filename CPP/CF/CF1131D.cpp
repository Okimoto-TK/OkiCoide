#include <cstdio>
#include <vector>
#include <queue>
#define N 1000
int n, m;
char buf[N + 5][N + 5];
int s[N * 2 + 5];
int deg[N * 2 + 5];
int f[N * 2 + 5];
int ans[N * 2 + 5];
std::vector<int> vec[N * 2 + 5];
std::queue<int> q;
int a(int x)
{
	return x;
}
int b(int x)
{
	return x + n;
}
int find(int x)
{
	if(s[x] == x) return x;
	return s[x] = find(s[x]);
}
void merge(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	if(fx == fy) return;
	s[fx] = fy;
}
void add_edge(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	vec[fx].push_back(fy);
	deg[fy]++;
}
int main()
{
	for(int i = 1; i <= N * 2; i++) s[i] = i;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", buf[i] + 1);
		for(int j = 1; j <= m; j++)
		{
			if(buf[i][j] == '=')
			{
				merge(a(i), b(j));
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(buf[i][j] == '<')
			{
				add_edge(a(i), b(j));
			}
			else if(buf[i][j] == '>')
			{
				add_edge(b(j), a(i));
			}
		}
	}
	for(int i = 1; i <= n + m; i++)
	{
		if(s[i] == i && deg[i] == 0)
		{
			q.push(i);
			f[i] = 1;
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(auto v : vec[u])
		{
			f[v] = std::max(f[v], f[u] + 1);
			if(--deg[v] == 0)
			{
				q.push(v);
			}
		}
	}
	for(int i = 1; i <= n + m; i++)
	{
		if(deg[i] > 0)
		{
			printf("No");
			return 0;
		}
		ans[i] = f[find(i)];
	}
	printf("Yes\n");
	for(int i = 1; i <= n; i++)
	{
		printf("%d ", ans[a(i)]);
	}
	printf("\n");
	for(int i = 1; i <= m; i++)
	{
		printf("%d ", ans[b(i)]);
	}
	return 0;
}