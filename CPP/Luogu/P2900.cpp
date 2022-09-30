#include <cstdio>
#include <algorithm>
#define N 50000
#define int long long
int n;
struct item
{
	long long w, l;
} fl[N + 5];
item it[N + 5];
bool cmp(item a, item b)
{
	if(a.w == b.w) return a.l < b.l;
	return a.w < b.w;
}
struct Vector
{
	long long x, y;
	Vector()
	{
		x = y = 0;
	}
	Vector(long long _x, long long _y)
	{
		x = _x, y = _y;
	}
	Vector operator-(const Vector & v) const
	{
		return Vector(x - v.x, y - v.y);
	}
	long long operator*(const Vector & v) const
	{
		return x * v.y - y * v.x;
	}
};
Vector con[N + 5];
long long f[N + 5];
int l, r;
void add(int i)
{
	Vector v(-it[i + 1].l, f[i]);
	while(r >= 2 && (con[r] - con[r - 1]) * (v - con[r]) <= 0)
	{
		r--;
	}
	con[++r] = v;
}
signed main()
{
	//freopen("in.in", "r", stdin);
	l = 1, r = 0;
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &it[i].w, &it[i].l);
	}
	std::sort(it + 1, it + 1 + n, cmp);
	int cnt=1;
	for(int i=2;i<=n;i++){
		while(cnt>=1&&it[i].l>=it[cnt].l)cnt--;
		it[++cnt]=it[i];
	}
	add(0);
	//printf("%d", cnt);
	for(int i = 1; i <= cnt; i++)
	{
		long long k = it[i].w;
		long long min = con[l].y - con[l].x * k;
		for(; l < r; l++)
		{
			if(con[l + 1].y - con[l + 1].x * k > min)
			{
				break;
			}
			min = con[l + 1].y - con[l + 1].x * k;
		}
		//printf("%lld\n", min);
		f[i] = min;
		//printf("%d %lld\n", i, f[i]);
		add(i);
	}
	printf("%lld", f[cnt]);
	return 0;
}
