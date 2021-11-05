#include <cstdio>
#include <cstring>
#include <queue>
int head[300005];
struct Edge
{
	int u, v, nxt;
	Edge() { u = v = nxt = 0; }
	Edge(int a, int b)
	{
		u = a;
		v = b;
		nxt = head[a];
	}
};
int n, ptr = 2, pool = 26;
char buf[60];
bool cnt[30];
bool vis[30];
bool rec[300005];
Edge e[6000005];
void addEdge(int a, int b)
{
	e[ptr] = Edge(a, b);
	head[a] = ptr++;
	e[ptr] = Edge(b, a);
	head[b] = ptr++;
}
std::queue<int> q;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		++pool;
		memset(cnt, 0 ,sizeof(cnt));
		scanf("%s", buf);
		int len = strlen(buf);
		for(int j = 0; j < len; j++)
		{
			if(cnt[buf[j] - 'a' + 1]) continue;
			cnt[buf[j] - 'a' + 1] = true;
			addEdge(pool, buf[j] - 'a' + 1);
			vis[buf[j] - 'a' + 1] = true;
		}
	}
	int ans = 0;
	for(int i = 1; i <= 26; i++)
	{
		if(!vis[i]) continue;
		if(rec[i]) continue;
		ans++;
		q.push(i);
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			for(int i = head[u]; i != 0; i = e[i].nxt)
			{
				if(rec[e[i].v]) continue;
				q.push(e[i].v);
				rec[e[i].v] = true;
			}
		}
	}
	printf("%d", ans);
	return 0;
}
