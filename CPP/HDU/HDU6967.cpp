#include <cstdio>
#define N 200000
const int mod = 1000000007;
int read()
{
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*w;
}
void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		print(x/10);
	putchar(x%10+'0');
	return;
}
struct Matrix
{
	int n, m;
	int a[7][7];
	Matrix()
	{
		for(int i = 1; i <= 6; i++)
		{
			for(int j = 1; j <= 6; j++)
			{
				a[i][j] = 0;
			}
		}
		n = m = 0;
	}
	Matrix(int x, int _n, int _m)
	{
		for(int i = 1; i <= 6; i++)
		{
			for(int j = 1; j <= 6; j++)
			{
				a[i][j] = 0;
			}
			a[i][i] = x;
		}
		n = _n;
		m = _m;
	}
	void reset(int x)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				a[i][j] = x;
			}
		}
	}
	Matrix operator*(const Matrix & A) const
	{
		Matrix R(0, n, A.m);
		for(int i = 1; i <= n; i++)
		{
			for(int k = (i == n ? m : 1); k <= m; k++)
			{
				if(a[i][k] == 0) continue;
				for(int j = 1; j <= A.m; j++)
				{
					(R.a[i][j] += 1ll * a[i][k] * A.a[k][j] % mod) %= mod;
				}
			}
		}
		return R;
	}
	Matrix operator+(const Matrix & A) const
	{
		Matrix R(0, n, m);
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				R.a[i][j] = (a[i][j] + A.a[i][j]) % mod;
			}
		}
		return R;
	}
};
Matrix op[5];
struct node
{
	Matrix mat;
	Matrix lazy;
	int l, r;
	bool e;
	node()
	{
		lazy = Matrix(1, 6, 6);
		e = true;
		mat.n = 6;
		mat.m = 1;
		l = r = 0;
	}
} t[(N << 1) + 5];
int n, pool;
long long vec[N + 5][2];
void push_up(int k)
{
	t[k].mat = t[t[k].l].mat + t[t[k].r].mat;
}
void build(int & k, int l, int r)
{
	if(k == 0) k = ++pool;
	if(l == r)
	{
		t[k].mat.a[1][1] = vec[l][0];
		t[k].mat.a[2][1] = vec[l][1];
		t[k].mat.a[3][1] = (vec[l][0] * vec[l][0]) % mod;
		t[k].mat.a[4][1] = (vec[l][1] * vec[l][1]) % mod;
		t[k].mat.a[5][1] = (vec[l][0] * vec[l][1]) % mod;
		t[k].mat.a[6][1] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(t[k].l, l, mid);
	build(t[k].r, mid + 1, r);
	push_up(k);
}
void update(int k, const Matrix & opt)
{
	if(t[k].e)
	{
		t[k].lazy = opt;
	}
	else
	{
		t[k].lazy = opt * t[k].lazy;
	}
	t[k].e = false;
	t[k].mat = opt * t[k].mat;
}
void push_down(int k)
{
	if(t[k].e) return;
	update(t[k].l, t[k].lazy);
	update(t[k].r, t[k].lazy);
	t[k].lazy.reset(1);
	t[k].e = true;
}
void change(int k, int l, int r, int x, int y, int opt)
{
	if(x <= l && r <= y)
	{
		update(k, op[opt]);
		return;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	if(x <= mid) change(t[k].l, l, mid, x, y, opt);
	if(y > mid) change(t[k].r, mid + 1, r, x, y, opt);
	push_up(k);
}
long long query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return t[k].mat.a[5][1] % mod;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	long long re = 0;
	if(x <= mid) (re += query(t[k].l, l, mid, x, y)) %= mod;
	if(y > mid) (re += query(t[k].r, mid + 1, r, x, y)) %= mod;
	return re;
}
int q;
int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
	op[1] = Matrix(1, 6, 6);
	op[1].n = op[1].m = op[2].n = op[2].m = op[3].n = op[3].m = 6;
	op[2].a[1][1] = 3;
	op[2].a[1][2] = 2;
	op[2].a[2][1] = 3;
	op[2].a[2][2] = -2;
	op[2].a[3][3] = 9;
	op[2].a[3][4] = 4;
	op[2].a[3][5] = 12;
	op[2].a[4][3] = 9;
	op[2].a[4][4] = 4;
	op[2].a[4][5] = -12;
	op[2].a[5][3] = 9;
	op[2].a[5][4] = -4;
	op[2].a[6][6] = 1;
	op[3].a[1][2] = 1;
	op[3].a[2][1] = 1;
	op[3].a[3][4] = 1;
	op[3].a[4][3] = 1;
	op[3].a[5][5] = 1;
	op[3].a[6][6] = 1;
	n = read();
	for(int i = 1; i <= n; i++)
	{
		vec[i][0] = read();
		vec[i][1] = read();
	}
	int root = 0;
	build(root, 1, n);
	q = read();
	for(int i = 1; i <= q; i++)
	{
		int opt, l, r;
		opt = read();
		if(opt == 1)
		{
			int tag;
			long long x;
			tag = read();
			l = read();
			r = read();
			x = read();
			if(tag == 0)
			{
				op[1].a[1][6] = x;
				op[1].a[3][1] = 2 * x % mod;
				op[1].a[3][6] = x * x % mod;
				op[1].a[5][2] = x;
			}
			else if(tag == 1)
			{
				op[1].a[2][6] = x;
				op[1].a[4][2] = 2 * x % mod;
				op[1].a[4][6] = x * x % mod;
				op[1].a[5][1] = x;
			}
			change(root, 1, n, l, r, opt);
			if(tag == 0)
			{
				op[1].a[1][6] = 0;
				op[1].a[3][1] = 0;
				op[1].a[3][6] = 0;
				op[1].a[5][2] = 0;
			}
			else if(tag == 1)
			{
				op[1].a[2][6] = 0;
				op[1].a[4][2] = 0;
				op[1].a[4][6] = 0;
				op[1].a[5][1] = 0;
			}			
		}
		else if(opt == 2 || opt == 3)
		{
			l = read();
			r = read();
			change(root, 1, n, l, r, opt);
		}
		else
		{
			l = read();
			r = read();
			print((query(root, 1, n, l, r) % mod + mod) % mod);
			putchar('\n');
		}
	}
	return 0;
}