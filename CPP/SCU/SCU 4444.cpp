#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
#include <algorithm>
#define N 100000
#define M 500000
long long n, m, p, a, b;
std::list<int> li;
std::queue<int> q;
int head[N + 5];
int cnt[N + 5];
bool vis[N + 5];
struct Edge
{
	int v, nxt;
} e[M * 2 + 5];
void add_edge(int u, int v)
{
	e[p].v = v;
	e[p].nxt = head[u];
	head[u] = p++;
	e[p].v = u;
	e[p].nxt = head[v];
	head[v] = p++;
}
int main()
{
	while(scanf("%lld", &n) != EOF)
	{
		p = 0;
		memset(head, -1, sizeof(head));
		memset(vis, 0, sizeof(vis));
		memset(e, 0, sizeof(e));
		memset(cnt, 0x3f, sizeof(cnt));
		li.clear();
		scanf("%lld%lld%lld", &m, &a, &b);
		bool flag = false;
		for(int i = 1; i <= m; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			if((u == 1 && v == n) || (u == n && v == 1))
			{
				flag = true;
			}
		}
		if(flag ^ (a > b))
		{
			printf("%lld\n", std::min(a, b));
			continue;
		}
		if(a <= b)
		{
			q.push(1);
			cnt[1] = 0;
			while(!q.empty())
			{
				int u = q.front();
				q.pop();
				if(vis[u]) continue;
				vis[u] = true;
				for(int i = head[u]; i != -1; i = e[i].nxt)
				{
					int v = e[i].v;
					cnt[v] = std::min(cnt[v], cnt[u] + 1);
					q.push(v);
				}
			}
			if(cnt[n] >= 0x3f3f3f3f)
			{
				printf("%lld\n", b);
				continue;
			}
			printf("%lld\n", std::min(1ll * b, 1ll * cnt[n] * a));
			continue;
		}
		for(int i = 2; i <= n; i++)
		{
			li.push_back(i);
		}
		q.push(1);
		cnt[1] = 0;
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			for(int i = head[u]; i != -1; i = e[i].nxt)
			{
				vis[e[i].v] = true;
			}
			for(auto it = li.begin(); it != li.end();)
			{
				if(vis[*it])
				{
					it++;
					continue;
				}
				cnt[*it] = std::min(cnt[u] + 1, cnt[*it]);
				q.push(*it);
				it = li.erase(it);
			}
			for(int i = head[u]; i != -1; i = e[i].nxt)
			{
				vis[e[i].v] = false;
			}
		}
		if(cnt[n] >= 0x3f3f3f3f)
		{
			printf("%lld\n", a);
			continue;
		}
		printf("%lld\n", std::min(a, 1ll * cnt[n] * b));
	}
	return 0;
}
