#include <cstdio>
#include <algorithm>
#define N 100000
int n;
long long a, b;
long long t[N + 5][2];
int lowbit(int x)
{
	return x & (-x);
}
void insert(int x, long long v)
{
	for(int i = x; i <= N; i += lowbit(i))
	{
		t[i][0]++;
		t[i][1] += v;
	}
}
long long query(int x, int op)
{
	long long re = 0;
	for(int i = x; i > 0; i -= lowbit(i))
	{
		re += t[i][op];
	}
	return re;
}
struct item
{
	int val, id;
} y[N + 5];
bool cmp(item i, item j)
{
	return i.val < j.val;
}
int x[N + 5];
int ord[N + 5];
long long getV(int mid)
{
	long long v = query(mid, 0);
	long long w = query(mid, 1);
	//printf("%d %lld %lld\n", mid, v, w);
	return (v * y[mid].val - w) * a + ((query(n, 1) - w) - (query(n, 0) - v) * y[mid].val) * b;
}
int main()
{
	scanf("%d%lld%lld", &n, &a, &b);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		y[i].val = x[i];
		y[i].id = i;
	}
	std::sort(y + 1, y + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		ord[y[i].id] = i;
	}
	for(int i = 1; i <= n; i++)
	{
		insert(ord[i], x[i]);
		int l = 1, r = n;
		long long lans, rans;
		while(l < r)
		{
			int lmid = l + (r - l) / 3;
			int rmid = r - (r - l) / 3;
			lans = getV(lmid);
			rans = getV(rmid);
			if(lans <= rans)
			{
				r = rmid - 1;
			}
			else
			{
				l = lmid + 1;
			}
		}
		printf("%lld\n", std::min(lans, rans));
	}
	return 0;
}