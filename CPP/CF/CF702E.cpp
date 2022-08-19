#include <cstdio>
#include <queue>
#include <vector>
#define N 100000
#define int long long
int n, k, pool, p;
int e[N + 5];
std::vector<int> g[N + 5];
long long v[N + 5];
int deg[N + 5];
std::queue<int> q;
bool done[N + 5];
bool vis[N + 5];
int rin[N + 5];
int start[N + 5];
int end[N + 5];
int rpr[N + 5];
int seg[N + 5];
int dep[N + 5];
int siz[N + 5];
int son[N + 5];
int fa[N + 5];
int top[N + 5];
int rsiz[N + 5];
int root[N + 5];
int dfs(int u)
{
	vis[u] = true;
	if(vis[e[u]])
	{
		vis[u] = false;
		end[++pool] = e[u];
		start[pool] = u;
		seg[u] = ++p;
		rpr[p] = u;
		rsiz[pool] = 1;
		rin[e[u]] = rin[u] = pool;
		done[u] = true;
		return u != e[u] ? pool : 0;
	}
	int r;
	if(!done[e[u]]) r = dfs(e[u]);
	else
	{
		vis[u] = false;
		done[u] = true;
		return 0;
	}
	vis[u] = false;
	if(rin[u])
	{
		seg[u] = ++p;
		rpr[p] = u;
		rsiz[pool]++;
		done[u] = true;
		return 0;
	}
	if(r)
	{
		seg[u] = ++p;
		rpr[p] = u;
		rsiz[pool]++;
	}
	done[u] = true;
	return rin[u] = r;
}
void dfs1(int u, int f, int rt)
{
	root[u] = rt;
	siz[u] = 1;
	dep[u] = dep[f] + 1;
	fa[u] = f;
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		dfs1(v, u, rt);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
void dfs2(int u)
{
	if(son[u])
	{
		int v = son[u];
		seg[v] = ++p;
		top[v] = top[u];
		rpr[p] = v;
		dfs2(v);
	}
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == son[u]) continue;
		seg[v] = ++p;
		top[v] = v;
		rpr[p] = v;
		dfs2(v);
	}
}
long long tsum[(N << 2) + 5];
long long tmin[(N << 2) + 5];
void build(int k, int l, int r)
{
	if(l == r)
	{
		tmin[k] = tsum[k] = v[rpr[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	tmin[k] = std::min(tmin[k << 1], tmin[k << 1 | 1]);
	tsum[k] = tsum[k << 1] + tsum[k << 1 | 1];
}
long long querysum(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return tsum[k];
	}
	int mid = (l + r) >> 1;
	long long sum = 0;
	if(x <= mid) sum += querysum(k << 1, l, mid, x, y);
	if(y > mid) sum += querysum(k << 1 | 1, mid + 1, r, x, y);
	return sum;
}
long long querymin(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return tmin[k];
	}
	int mid = (l + r) >> 1;
	long long min = 1e15;
	if(x <= mid) min = std::min(min, querymin(k << 1, l, mid, x, y));
	if(y > mid) min = std::min(min, querymin(k << 1 | 1, mid + 1, r, x, y));
	return min;
}
void ask(int x, int _k, long long &sum, long long &min)
{
	int fx = top[x];
	while(_k > dep[x] - dep[fx] + 1)
	{
		_k -= dep[x] - dep[fx] + 1;
		sum += querysum(1, 1, p, seg[fx], seg[x]);
		min = std::min(min, querymin(1, 1, p, seg[fx], seg[x]));
		x = fa[fx];
		fx = top[x];
	}
	sum += querysum(1, 1, p, seg[x] - _k + 1, seg[x]);
	min = std::min(min, querymin(1, 1, p, seg[x] - _k + 1, seg[x]));
}
void query(int x, long long &sum, long long &min)
{
	sum = 0;
	min = 1e10;
	int _k = k;
	if(rin[x])
	{
		int u = x;
		int no = rin[x];
		if(_k >= rsiz[no])
		{
			//printf("%d\n", rsiz[no]);
			min = std::min(min, querymin(1, 1, p, seg[start[no]], seg[end[no]]));
			sum = _k / rsiz[no] * querysum(1, 1, p, seg[start[no]], seg[end[no]]);
			_k %= rsiz[no];
		}
		if(seg[u] - seg[start[no]] + 1 >= _k)
		{
			min = std::min(min, querymin(1, 1, p, seg[u] - _k + 1, seg[u]));
			sum += querysum(1, 1, p, seg[u] - _k + 1, seg[u]);
		}
		else
		{
			min = std::min(min, querymin(1, 1, p, seg[start[no]], seg[u]));
			sum += querysum(1, 1, p, seg[start[no]], seg[u]);
			_k -= seg[u] - seg[start[no]] +  1;
			min = std::min(min, querymin(1, 1, p, seg[end[no]] - _k + 1, seg[end[no]]));
			sum += querysum(1, 1, p, seg[end[no]] - _k + 1, seg[end[no]]);
		}
	}
	else
	{
		if(_k > dep[x])
		{
			ask(x, dep[x], sum, min);
			_k -= dep[x];
			int no = rin[e[root[x]]];
			int u = e[root[x]];
			if(_k >= rsiz[no])
			{
				min = std::min(min, querymin(1, 1, p, seg[start[no]], seg[end[no]]));
				sum += _k / rsiz[no] * querysum(1, 1, p, seg[start[no]], seg[end[no]]);
				_k %= rsiz[no];
			}
			if(seg[u] - seg[start[no]] + 1 >= _k)
			{
				min = std::min(min, querymin(1, 1, p, seg[u] - _k + 1, seg[u]));
				sum += querysum(1, 1, p, seg[u] - _k + 1, seg[u]);
			}
			else
			{
				//printf("%d %d %d %d\n", u, no, seg[start[no]], seg[end[no]]);
				min = std::min(min, querymin(1, 1, p, seg[start[no]], seg[u]));
				sum += querysum(1, 1, p, seg[start[no]], seg[u]);
				_k -= seg[u] - seg[start[no]] +  1;
				min = std::min(min, querymin(1, 1, p, seg[end[no]] - _k + 1, seg[end[no]]));
				sum += querysum(1, 1, p, seg[end[no]] - _k + 1, seg[end[no]]);
			}
		}
		else
		{
			ask(x, _k, sum, min);
		}
	}
}
signed main()
{
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &e[i]);
		e[i]++;
		deg[e[i]]++;
		g[e[i]].push_back(i);
	}
	for(int i = 1; i <= n; i++)
	{
		if(deg[i] == 0) q.push(i);
		scanf("%lld", &v[i]);
	}
	while(!q.empty())
	{
		dfs(q.front());
		//printf("%d\n", q.front());
		q.pop();
	}
	for(int i = 1; i <= n; i++)
	{
		if(rin[e[i]] && !rin[i])
		{
			dfs1(i, 0, i);
			seg[i] = ++p;
			rpr[p] = i;
			top[i] = i;
			dfs2(i);
		}
		if(!done[i])
		{
			dfs(i);
		}
	}
	/*
	for(int i = 1; i <= n; i++)
	{
		printf("%d %d\n", i, dep[i]);
	}
	*/
	build(1, 1, p);
	for(int i = 1; i <= n; i++)
	{
		long long sum, min;
		query(i, sum, min);
		printf("%lld %lld\n", sum, min);
	}
	return 0;
}