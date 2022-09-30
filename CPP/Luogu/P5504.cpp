#include <cstdio>
#include <vector>
#define N 100000
#define S 10000
#define int long long
int n;
int col[N + 5];
int _col[N + 5];
int s[N + 5];
int _s[N + 5];
int cnt[S + 5];
__int128 f[N + 5];
struct Vector
{
	__int128 x, y;
	Vector()
	{
		x = y = 0;
	}
	Vector(long long a, long long b)
	{
		x = a, y = b;
	}
	__int128 operator*(const Vector & v) const
	{
		return x * v.y - y * v.x;
	}
	Vector operator-(const Vector & v) const
	{
		return Vector(x - v.x, y - v.y);
	}
};
std::vector<Vector> con[S + 5];
void add(int i)
{
	Vector v(_s[i], f[i] + 1ll * _col[i] * _s[i] * _s[i]);
	std::vector<Vector> & cc = con[_col[i]];
	while(cc.size() >= 2 && (cc.back() - cc[cc.size() - 2]) * (v - cc.back()) >= 0)
	{
		cc.pop_back();
	}
	cc.push_back(Vector(_s[i], f[i] + 1ll * _col[i] * _s[i] * _s[i]));
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &col[i]);
		_col[i - 1] = col[i];
	}
	for(int i = 1; i <= n; i++)
	{
		s[i] = ++cnt[col[i]];
		_s[i] = cnt[_col[i]];
	}
	add(0);
	for(int i = 1; i <= n; i++)
	{
		//printf("--%d\n", i);
		std::vector<Vector> & cc = con[col[i]];
		long long k = 2ll * col[i] * s[i];
		long long maxv = cc.back().y - cc.back().x * k;
		while(cc.size() >= 2)
		{
			//printf("%d %lld %lld %lld\n", max, (long long)cc[max].x, (long long)cc[max].y, k);
			if(cc[cc.size() - 2].y - cc[cc.size() - 2].x * k >= maxv)
			{
				maxv = cc[cc.size() - 2].y - cc[cc.size() - 2].x * k;
				cc.pop_back();
			}
			else
			{
				break;
			}
		}
		//printf("%lld\n", ptr[col[i]]);
		f[i] = maxv + 1ll * col[i] * s[i] * s[i];
		//printf("%lld\n", (long long)f[i]);
		add(i);
	}
	printf("%lld", (long long)f[n]);
	return 0;
}
