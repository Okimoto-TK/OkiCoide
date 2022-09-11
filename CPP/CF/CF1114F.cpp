#include <cstdio>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <unordered_map>
const int mod = 1e9 + 7;
int tot, pool, n, q;
int a[400005];
long long inv[305];
long long fac[305];
long long loc[800005];
long long lazy[800005];
bool npr[305];
int pr[305];
std::unordered_map<long long, int> lg;
struct node
{
	int lc, rc;
	long long oc;
	long long prod;
	node()
	{
		lc = rc = oc = 0;
		prod = 1;
	}
	long long getPhi()
	{
		long long re = prod;
		for(long long i = oc; i > 0; i -= (i & (-i)))
		{
			int j = lg[i & (-i)] + 1;
			(re *= inv[j] * (pr[j] - 1) % mod) %= mod;
		}
		return re;
	}
} t[800005];
void esv()
{
	for(int i = 2; i <= 300; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && i * pr[j] <= 300; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				break;
			}
		}
	}
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
void pre()
{
	for(int i = 2; i <= 300; i++)
	{
		int x = i;
		for(int j = 1; j <= tot && x != 1; j++)
		{
			if(i % pr[j] == 0)
			{
				fac[i] |= (1ll << (j - 1));
			}
		}
	}
	for(int i = 1; i <= tot; i++)
	{
		inv[i] = power(pr[i], mod - 2);
	}
	for(long long x = 1, i = 0; i <= 62; x <<= 1, i++)
	{
		lg[x] = i;
	}
}
node merge(const node & l, const node & r)
{
	node re;
	re.prod = l.prod * r.prod % mod;
	re.oc = l.oc | r.oc;
	return re;
}
node merge(int l, int r)
{
	node re;
	re.prod = t[l].prod * t[r].prod % mod;
	re.oc = t[l].oc | t[r].oc;
	re.lc = l;
	re.rc = r;
	return re;
}
void build(int & k, int l, int r)
{
	if(k == 0) k = ++pool;
	lazy[k] = 1;
	if(l == r)
	{
		t[k].prod = power(a[l], r - l + 1);
		t[k].oc |= fac[a[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(t[k].lc, l, mid);
	build(t[k].rc, mid + 1, r);
	t[k] = merge(t[k].lc, t[k].rc);
	//printf("%d %lld\n", k, t[k].prod);
}
void update(int k, int l, int r, int v, long long voc)
{
	(t[k].prod *= power(v, r - l + 1)) %= mod;
	t[k].oc |= voc;
	loc[k] |= voc;
	(lazy[k] *= v) %= mod;
}
void push_down(int k, int l, int r)
{
	if(lazy[k] == 1) return;
	int mid = (l + r) >> 1;
	update(t[k].lc, l, mid, lazy[k], loc[k]);
	update(t[k].rc, mid + 1, r, lazy[k], loc[k]);
	lazy[k] = 1;
	loc[k] = 0;
}
void change(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		update(k, l, r, v, fac[v]);
		return;
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	if(x <= mid) change(t[k].lc, l, mid, x, y, v);
	if(y > mid) change(t[k].rc, mid + 1, r, x, y, v);
	t[k] = merge(t[k].lc, t[k].rc);
}
node query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		//printf("%d %lld\n", k, t[k].prod);
		return t[k];
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	node re;
	re.oc = 0;
	re.prod = 1;
	if(x <= mid)
	{
		re = merge(re, query(t[k].lc, l, mid, x, y));
	}
	if(y > mid)
	{
		re = merge(re, query(t[k].rc, mid + 1, r, x, y));
	}
	//printf("%d %d %lld\n", l, r, re.prod);
	return re;
}
int main()
{
	esv();
	pre();
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	int root = 0;
	build(root, 1, n);
	for(int i = 1; i <= q; i++)
	{
		char opt[10];
		scanf("%s", opt);
		if(opt[0] == 'T')
		{
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%lld\n", (query(root, 1, n, l, r).getPhi()));
		}
		else
		{
			int l, r, x;
			scanf("%d%d%d", &l, &r, &x);
			change(root, 1, n, l, r, x);
		}
	}
	return 0;
}