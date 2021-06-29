#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#define N 200014
int n, m, q, pool;
std::vector<int> g[N]; 
int B[N];
double f[N][3];
double son[N];
void dfs1(int u, int fa)
{
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == fa) continue;
		dfs1(v, u);
		if(f[u][0] < f[v][0] + 1)
		{
			f[u][1] = f[u][0];
			f[u][0] = f[v][0] + 1;
			son[u] = v;
		}
		else if(f[u][1] < f[v][0] + 1) f[u][1] = f[v][0] + 1;
	}
}
void dfs2(int u, int fa)
{
	B[u] = pool;
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == fa) continue;
		if(v == son[u]) f[v][2] = std::max(f[u][1] + 1, f[u][2] + 1);
		else f[v][2] = std::max(f[u][0] + 1, f[u][2] + 1);
		dfs2(v, u);
	}
}
double d[N];
double D[N];
std::vector<double> _d[N];
std::vector<double> t[N];
std::vector<double> sum[N];
std::map<int, double> ans[N];
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 1; i <= n; i++)
	{
		if(B[i] != 0) continue;
		pool++;
		dfs1(i, 0);
		dfs2(i, 0);
	}
	for(int i = 1; i <= n; i++)
	{
		d[i] = std::max(f[i][0], f[i][2]);
		D[B[i]] = std::max(D[B[i]], d[i]);
		_d[B[i]].push_back(d[i]);
		t[B[i]].push_back(i);
	};
	for(int i = 1; i <= pool; i++) std::sort(_d[i].begin(), _d[i].end());
	for(int i = 1; i <= pool; i++)
	{
		sum[i].push_back(0);
		int len = _d[i].size();
		for(int j = 0; j < len; j++)
		{
			int x = _d[i][j];
			sum[i].push_back(sum[i][j] + x);
		}
	}
	for(int i = 1; i <= q; i++)
	{
		int _u, _v;
		scanf("%d%d", &_u, &_v);
		if(B[_u] == B[_v])
		{
			printf("-1\n");
			continue;
		}
		if(t[B[_u]].size() > t[B[_v]].size()) std::swap(_u, _v);
		if(ans[B[_u]][B[_v]] != 0)
		{
			printf("%.10lf\n", ans[B[_u]][B[_v]]);
			continue;
		}
		double dis = std::max(D[B[_u]], D[B[_v]]);
		int len = t[B[_u]].size();
		int _len = t[B[_v]].size();
		double ex = 0;
		double dv = double(len) * double(_len);
		for(int j = 0; j < len; j++)
		{
			int u = t[B[_u]][j];
			double ptr = double(std::lower_bound(_d[B[_v]].begin(), _d[B[_v]].end(), dis - d[u] - 1) - _d[B[_v]].begin());
			ex += d[u] / double(len);
			ex += ptr * (dis - d[u]) / dv;
			ex += (sum[B[_v]][_len] - sum[B[_v]][ptr]) / dv;
			ex += (_len - ptr) / dv;
		}
		printf("%.10lf\n", ex);
		ans[B[_u]][B[_v]] = ex;
	}
	return 0;
}
