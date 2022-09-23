#include <cstdio>
#include <vector>
#define N 5000
#define M 500000
int n, m, pool;
struct node
{
	std::vector<int> op;
} t[M * 4 + 5];
int a[N + 5][N + 5];
int q[M + 5];
int ans[M + 5];
int ti[N + 5][N + 5];
struct opr
{
	int x, y;
} o[M + 5];
int s[N + 5];
int siz[N + 5];
int find(int x)
{
	if(s[x] == x) return x;
	return find(s[x]);
}
std::vector<std::pair<int, int> > rec;
void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if(fx == fy)
	{
		rec.push_back(std::make_pair(-1, -1));
		return;
	}
	if(siz[fx] > siz[fy])
	{
		std::swap(fx, fy);
	}
	siz[fy] += siz[fx];
	s[fx] = fy;
	rec.push_back(std::make_pair(fx, fy));
}
void undo()
{
	auto last = rec.back();
	rec.pop_back();
	if(last.first == -1) return;
	s[last.first] = last.first;
	siz[last.second] -= siz[last.first];
}
void insert(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		t[k].op.push_back(v);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) insert(k << 1, l, mid, x, y, v);
	if(y > mid) insert(k << 1 | 1, mid + 1, r, x, y, v);
}
void solve(int k, int l, int r)
{
	int len = t[k].op.size();
	for(int i = 0; i < len; i++)
	{
		merge(o[t[k].op[i]].x, o[t[k].op[i]].y);
	}
	if(l == r)
	{
		if(q[l] != 0)
		{
			if(find(o[q[l]].x) == find(o[q[l]].y))
			{
				ans[l] = true;
			}
		}
		for(int i = 0; i < len; i++)
		{
			undo();
		}
		return;
	}
	int mid = (l + r) >> 1;
	solve(k << 1, l, mid);
	solve(k << 1 | 1, mid + 1, r);
	for(int i = 0; i < len; i++)
	{
		undo();
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		s[i] = i;
		siz[i] = 1;
	}
	for(int i = 1; i <= m; i++)
	{
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if(op == 0)
		{
			a[x][y] = a[y][x] = ++pool;
			o[pool].x = x;
			o[pool].y = y;
			ti[x][y] = ti[y][x] = i;
		}
		else if(op == 1)
		{
			insert(1, 1, m, ti[x][y], i, a[x][y]);
			a[x][y] = a[y][x] = 0;
			ti[x][y] = ti[y][x] = 0;
		}
		else
		{
			o[++pool].x = x;
			o[pool].y = y;
			q[i] = pool;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = i; j <= n; j++)
		{
			if(a[i][j])
			{
				insert(1, 1, m, ti[i][j], m, a[i][j]);
			}
		}
	}
	solve(1, 1, m);
	for(int i = 1; i <= m; i++)
	{
		if(q[i] != 0)
		{
			printf("%s\n", ans[i] ? "Y" : "N");
		}
	}
	return 0;
}
