#include <cstdio>
#define N 50000
struct node
{
	bool none;
	int lhead, rhead, headl, headr;
	int l, r;
	void print()
	{
		printf("[%d %d] [%d %d] [%d %d]\n", l, lhead, headl, headr, rhead, r);
	}
};
node merge(node x, node y)
{
	//x.print();
	//y.print();
	node re;
	if(x.none && y.none)
	{
		re.none = true;
		re.l = x.l;
		re.r = y.r;
		
		re.lhead = re.rhead = re.headl = re.headr = -1;
		//re.print();
		//printf("---------\n");
		return re;
	}
	re.none = false;
	if(x.none)
	{
		re.l = x.l;
		re.r = y.r;
		re.lhead = -1;
		re.rhead = y.rhead;
		re.headl = y.headl;
		re.headr = y.headr;
		//re.print();	
		//printf("---------\n");
		return re;
	}
	if(y.none)
	{
		re.l = x.l;
		re.r = y.r;
		re.lhead = x.lhead;
		re.rhead = -1;
		re.headl = x.headl;
		re.headr = x.headr;
		//re.print();
		//printf("---------\n");
		return re;
	}
	if(x.lhead == x.r && y.lhead != -1)
	{
		re.lhead = y.lhead;
	}
	else
	{
		re.lhead = x.lhead;
	}
	if(y.rhead == y.l && x.rhead != -1)
	{
		re.rhead = x.rhead;
	}
	else
	{
		re.rhead = y.rhead;
	}
	re.headl = x.headl;
	re.headr = x.headr;
	if(y.lhead != -1 && x.rhead != -1 && y.lhead - x.rhead > re.headr - re.headl)
	{
		re.headr = y.lhead;
		re.headl = x.rhead;
 	}
 	if(y.headr - y.headl > re.headr - re.headl)
 	{
 		re.headr = y.headr;
 		re.headl = y.headl;
 	}
 	re.l = x.l;
 	re.r = y.r;
 	//re.print();
 	//printf("---------\n");
 	return re;
}
node t[N * 8 + 5];
int lazy[N * 8 + 5];
void build(int k, int l, int r)
{
	lazy[k] = -1;
	if(l == r)
	{
		t[k].none = false;
		t[k].l = t[k].r = t[k].lhead = t[k].rhead = t[k].headl = t[k].headr = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	t[k] = merge(t[k << 1], t[k << 1 | 1]);
}
void cover(int k, int v)
{
	if(v == 1)
	{
		t[k].none = true;
		lazy[k] = v;
		t[k].lhead = -1;
		t[k].rhead = -1;
		t[k].headl = -1;
		t[k].headr = -1;
		return;
	}
	t[k].none = false;
	lazy[k] = v;
	t[k].lhead = t[k].r;
	t[k].rhead = t[k].l;
	t[k].headl = t[k].l;
	t[k].headr = t[k].r;
}
void push_down(int k)
{
	if(lazy[k] == -1) return;
	cover(k << 1, lazy[k]);
	cover(k << 1 | 1, lazy[k]);
	lazy[k] = -1;
}
void modify(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		cover(k, v);
		return;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	if(x <= mid) modify(k << 1, l, mid, x, y, v);
	if(y > mid) modify(k << 1 | 1, mid + 1, r, x, y, v);
	t[k] = merge(t[k << 1], t[k << 1 | 1]);
}
int find(int k, int l, int r, int len)
{
	if(t[k].none) return -1;
	if(t[k].headr - t[k].headl + 1 < len) return -1;
	if(l == r)
	{
		return l;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	if(!t[k << 1].none && t[k << 1].headr - t[k << 1].headl + 1 >= len) return find(k << 1, l, mid, len);
	if(t[k << 1].rhead != -1 && t[k << 1 | 1].lhead != -1 && t[k << 1 | 1].lhead - t[k << 1].rhead + 1 >= len) return t[k << 1].rhead;
	if(!t[k << 1 | 1].none && t[k << 1 | 1].headr - t[k << 1 | 1].headl + 1 >= len) return find(k << 1 | 1, mid + 1, r, len);
	t[k] = merge(t[k << 1], t[k << 1 | 1]);
	return -1;
}
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for(int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int x;
			scanf("%d", &x);
			int ptr = find(1, 1, n, x);
			printf("%d\n", ptr == -1 ? 0 : ptr);
			if(ptr != -1) modify(1, 1, n, ptr, ptr + x - 1, 1);
		}
		else
		{
			int l, r;
			scanf("%d%d", &l, &r);
			modify(1, 1, n, l, l + r - 1, 0);
		}
	}
}