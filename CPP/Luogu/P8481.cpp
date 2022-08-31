#include <cstdio>
#include <algorithm>
int get(int *num,int x,int l,int r)
{
	if(l==r) return 0;
	int re = 0x3f3f3f3f;
	int mid=(l+r)/2;
	if(num[mid]<x)
	{
		re = 1 + get(num,x,mid+1,r);
	}
	else
	{
		re = 1 + get(num,x,l,mid);
	}
	int _mid = (l + r + 1) >> 1;
	if(num[_mid]-1<x)
	{
		re = std::min(re, 1 + get(num,x,_mid,r));
	}
	else
	{
		re = std::min(re, 1 + get(num,x,l,_mid - 1));
	}
	return re;
}
int find(int *num,int x,int len)
{
	return get(num,x,0,len-1);
}
int n, q;
int num[(1 << 20) + 5];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &num[i]);
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int x;
		scanf("%d", &x);
		printf("%d\n", find(num, x, n));
	}
	return 0;
}