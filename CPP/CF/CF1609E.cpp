#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100000
const int inf = 0x3f3f3f3f;
struct Matrix
{
	int n, m;
	int a[3][3];
	Matrix()
	{
		n = m = 0;
		memset(a, 0, sizeof(a));
	}
	Matrix(int _n, int _m, int v)
	{
		n = _n, m = _m;
		memset(a, v, sizeof(a));
	}
	Matrix operator*(const Matrix & x) const
	{
		Matrix r(n, x.m, 0x3f);
		for(int k = 0; k < m; k++)
		{
			for(int i = 0; i < n; i++)
			{
				if(a[i][k] == inf) continue;
				for(int j = 0; j < x.m; j++)
				{
					r.a[i][j] = std::min(r.a[i][j], a[i][k] + x.a[k][j]);
				}
			}
		}
		return r;
	}
};
int n, q;
char s[N + 5];
Matrix op[3];
Matrix t[N * 4 + 5];
void build(int k, int l, int r)
{
	if(l == r)
	{
		t[k] = op[s[l] - 'a'];
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	t[k] = t[k << 1 | 1] * t[k << 1];
}
void change(int k, int l, int r, int x, int v)
{
	if(l == r)
	{
		t[k] = op[v];
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		change(k << 1, l, mid, x, v);
	}
	else
	{
		change(k << 1 | 1, mid + 1, r, x, v);
	}
	t[k] = t[k << 1 | 1] * t[k << 1];
}
int query()
{
	Matrix r(3, 1, 0x3f);
	r.a[0][0] = 0;
	r = t[1] * r;
	return std::min(std::min(r.a[0][0], r.a[1][0]), r.a[2][0]);
}
int main()
{
	for(int i = 0; i < 3; i++) op[i] = Matrix(3, 3, 0x3f);
	op[0].a[0][0] = op[0].a[2][1] = 1;
	op[0].a[1][0] = op[0].a[1][1] = op[0].a[2][2] = 0;
	op[1].a[0][0] = op[1].a[2][1] = op[1].a[2][2] = 0;
	op[1].a[1][0] = op[1].a[1][1] = 1;
	op[2].a[0][0] = op[2].a[1][1] = 0;
	op[2].a[1][0] = op[2].a[2][1] = op[2].a[2][2] = 1;
	scanf("%d%d", &n, &q);
	scanf("%s", s + 1);
	build(1, 1, n);
	for(int i = 1; i <= q; i++)
	{
		int x;
		char v[2];
		scanf("%d%s", &x, v);
		change(1, 1, n, x, v[0] - 'a');
		printf("%d\n", query());
	}
	return 0;
}
