#include <cstdio>
#include <vector>
#define N 1000002
int n, m;
int t1[N * 4 + 5];
int t2[N * 4 + 5];
std::vector<int> q1[N + 5];
std::vector<int> q2[N + 5];
int s1[N + 5][2];
int s2[N + 5][2];
void change(int * t, int k, int l, int r, int x, int v)
{
	if(l == r)
	{
		t[k] = v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		change(t, k << 1, l, mid, x, v);
	}
	else
	{
		change(t, k << 1 | 1, mid + 1, r, x, v);
	}
	t[k] = t[k << 1] + t[k << 1 | 1];
}
int query(int * t, int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return t[k];
	}
	int mid = (l + r) >> 1;
	int re = 0;
	if(x <= mid)
	{
		re += query(t, k << 1, l, mid, x, y);
	}
	if(y > mid)
	{
		re += query(t, k << 1 | 1, mid + 1, r, x, y);
	}
	return re;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int y, x1, x2;
		scanf("%d%d%d", &y, &x1, &x2);
		y++;
		x1++;
		x2++;
		s1[y][0] = x1;
		s1[y][1] = x2;
		q1[x1].push_back(y);
		q1[x2 + 1].push_back(-y);
	}
	s1[1][0] = 1;
	s1[1][1] = N - 1;
	q1[1].push_back(1);
	q1[N].push_back(-1);
	s1[N - 1][0] = 1;
	s1[N - 1][1] = N - 1;
	q1[1].push_back(N - 1);
	q1[N].push_back(-N + 1);
	for(int i = 1; i <= m; i++)
	{
		int x, y1, y2;
		scanf("%d%d%d", &x, &y1, &y2);
		x++;
		y1++;
		y2++;
		s2[x][0] = y1;
		s2[x][1] = y2; 
		q2[y1].push_back(x);
		q2[y2 + 1].push_back(-x);
	}
	s2[1][0] = 1;
	s2[1][1] = N - 1;
	q2[1].push_back(1);
	q2[N].push_back(-1);
	s2[N - 1][0] = 1;
	s2[N - 1][1] = N - 1;
	q2[1].push_back(N - 1);
	q2[N].push_back(-N + 1);
	long long edge = 0;
	long long vertex = 0;
	long long _vertex = 0;
	for(int i = 1; i <= N; i++)
	{
		for(auto x : q1[i])
		{
			change(t1, 1, 1, N, x > 0 ? x : -x, x > 0 ? 1 : 0);
		}
		for(auto x : q2[i])
		{
			change(t2, 1, 1, N, x > 0 ? x : -x, x > 0 ? 1 : 0);
		}
		int vtmp = 0;
		if(s2[i][0] != 0)
		{
			vtmp += query(t1, 1, 1, N, s2[i][0], s2[i][1]);
			_vertex += vtmp;
			vtmp += (query(t1, 1, 1, N, s2[i][0], s2[i][0]) == 0 ? 1 : 0);
			vtmp += (query(t1, 1, 1, N, s2[i][1], s2[i][1]) == 0 ? 1 : 0);
			//printf("s %d %d\n", i - 1, vtmp);
			edge += vtmp - 1;
			vertex += vtmp;
		}
		if(s1[i][0] != 0)
		{
			vtmp = 0;
			vtmp += query(t2, 1, 1, N, s1[i][0], s1[i][1]);
			_vertex += vtmp;
			vtmp += (query(t2, 1, 1, N, s1[i][0], s1[i][0]) == 0 ? 1 : 0);
			vtmp += (query(t2, 1, 1, N, s1[i][1], s1[i][1]) == 0 ? 1 : 0);
			//printf("h %d %d\n", i - 1, vtmp);
			edge += vtmp - 1;
			vertex += vtmp;
		}
	}
	//printf("%lld\n", edge);
	printf("%lld", edge - (vertex - _vertex / 2) + 1);
	return 0;
} 
