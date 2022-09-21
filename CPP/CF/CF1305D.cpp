#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
int n;
bool tag[1005];
bool cnn[1005][1005];
std::vector<int> vec[1005];
int s, tar;
std::queue<int> q;
int dfs1(int u, int fa)
{
	if(u == tar) return 1;
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		if(dfs1(v, u) == 1)
		{
			if(u == s)
			{
				return v;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}
void dfs2(int u, int fa)
{
	tag[u] = true;
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs2(v, u);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		cnn[u][v] = cnn[v][u] = true;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	for(int i =1; i <= n; i++)
	{
		q.push(i);
	}
	while(q.size() >= 2)
	{
		int u1 = q.front();
		int cnt = 1;
		q.pop();
		while(cnt <= n && tag[u1])
		{
			cnt++;
			q.push(u1);
			u1 = q.front();
			q.pop();
		}
		int u2 = q.front();
		q.pop();
		cnt = 1;
		while(cnt <= n && (tag[u2] || cnn[u1][u2]))
		{
			cnt++;
			q.push(u2);
			u2 = q.front();
			q.pop();
		}
		if(cnn[u1][u2])
		{
			cnt = 1;
			while(cnt <= n && (tag[u1] || cnn[u1][u2]))
			{
				cnt++;
				q.push(u1);
				u1 = q.front();
				q.pop();
			}
		}
		printf("? %d %d\n", u1, u2);
		fflush(stdout);
		int c;
		scanf("%d", &c);
		if(u1 == c)
		{
			s = c;
			tar = u2;
			int v = dfs1(c, 0);
			dfs2(v, c);
		}
		else if(u2 == c)
		{
			s = c;
			tar = u1;
			int v = dfs1(c, 0);
			dfs2(v, c);
		}
		else
		{
			s = c;
			tar = u1;
			int v = dfs1(c, 0);
			dfs2(v, c);
			tar = u2;
			v = dfs1(c, 0);
			dfs2(v, c);
		}
	}
	for(int i = 1; n <= n; i++)
	{
		if(!tag[i])
		{
			printf("! %d\n", i);
			return 0;
		}
	}
	return 0;
}
