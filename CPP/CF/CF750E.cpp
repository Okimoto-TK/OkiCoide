#include <cstdio>
#include <algorithm>
#define K 5
#define N 200000
struct Matrix
{
	int n, m;
	int a[K][K];
	Matrix()
	{
		n = m = 0;
		for(int i = 0; i < K; i++)
		{
			for(int j = 0; j < K; j++)
			{
				a[i][j] = 0x3f3f3f3f;
			}
		}
	}
	Matrix(int _n, int _m)
	{
		n = _n;
		m = _m;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				a[i][j] = 0x3f3f3f3f;
			}
		}
	}
	Matrix(int _n, int _m, int v)
	{
		n = _n;
		m = _m;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				a[i][j] = v;
			}
		}
	}
	Matrix operator* (const Matrix & A) const
	{
		Matrix R(n, A.m);
		for(int k = 0; k < m; k++)
		{
			for(int i = 0; i < n; i++)
			{
				if(a[i][k] >= 0x3f3f3f3f) continue;
				for(int j = 0; j < A.m; j++)
				{
					R.a[i][j] = std::min(R.a[i][j], a[i][k] + A.a[k][j]);
				}
			}
		}
		return R;
	}
	void print()
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(a[i][j] < 0x3f3f3f3f) printf("%d\t", a[i][j]);
				else printf("inf\t");
			}
			printf("\n");
		}
	}
};
int n, q;
Matrix op[10];
int s[N + 5];
Matrix t[N * 4 + 5];
void build(int k, int l, int r)
{
	if(l == r)
	{
		t[k] = op[s[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	t[k] = t[k << 1 | 1] * t[k << 1];
}
Matrix query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return t[k];
	}
	int mid = (l + r) >> 1;
	if(x <= mid && y > mid)
	{
		return query(k << 1 | 1, mid + 1, r, x, y) * query(k << 1, l, mid, x, y);
	}
	else if(x <= mid)
	{
		return query(k << 1, l, mid, x, y);
	}
	else
	{
		return query(k << 1| 1, mid + 1, r, x, y);
	}
}
Matrix base;
int main()
{
	for(int i = 0; i < 10; i++)
	{
		op[i].n = op[i].m = K;
	}
	base.n = K;
	base.m = 1;
	base.a[0][0] = 0;
	op[2].a[0][0] = 1;
	op[2].a[1][0] = op[2].a[1][1] = op[2].a[2][2] = op[2].a[3][3] = op[2].a[4][4] = 0;
	op[0].a[0][0] = op[0].a[2][1] = op[0].a[2][2] = op[0].a[3][3] = op[0].a[4][4] = 0;
	op[0].a[1][1] = 1;
	op[1].a[0][0] = op[1].a[1][1] = op[1].a[3][2] = op[1].a[3][3] = op[1].a[4][4] = 0;
	op[1].a[2][2] = 1;
	op[6].a[0][0] = op[6].a[1][1] = op[6].a[2][2] = 0;
	op[6].a[3][3] = op[6].a[4][4] = 1;
	op[7].a[0][0] = op[7].a[1][1] = op[7].a[2][2] = op[7].a[4][3] = op[7].a[4][4] = 0;
	op[7].a[3][3] = 1;
	op[3].a[0][0] = op[3].a[1][1] = op[3].a[2][2] = op[3].a[3][3] = op[3].a[4][4] = 0;
	op[4] = op[5] = op[8] = op[9] = op[3];
	/*
	for(int i = 0; i < 10; i++)
	{
		printf("---%d---\n", i);
		op[i].print();
		printf("--------\n");
	}
	*/
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++)
	{
		scanf("%1d", &s[i]);
	}
	build(1, 1, n);
	for(int i = 1; i <= q; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		Matrix re = query(1, 1, n, l, r);
		//re.print();
		re = re * base;
		//re.print();
		if(re.a[4][0] >= 0x3f3f3f3f)
		{
			printf("-1\n");
		}
		else printf("%d\n", re.a[4][0]);
	}
	return 0;
}
