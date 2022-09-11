#include <cstdio>
#define N 100000
struct vec
{
	long long x, y;
	vec()
	{
		x = y = 0;
	}
	vec(long long a, long long b)
	{
		x = a;
		y = b;
	}
	vec operator-(const vec & a)
	{
		vec r = vec(x - a.x, y - a.y);
		return r;
	}
	long long operator*(const vec & a)
	{
		return x * a.y - y * a.x;
	}
};
int top;
vec stk[N + 5];
void insert(vec x)
{
	while(top > 0 && (x - stk[top]) * (stk[top] - stk[top - 1]) <= 0) top--;
	stk[++top] = x;
}
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		long long v;
		scanf("%lld", &v);
		vec tmp = vec(i, v * N);
		insert(tmp);
	}
	insert(vec(n + 1, 0));
	for(int i = 1; i <= n; i++)
	{
		int p = 0;
		while(p < top && stk[p].x < i) p++;
		if(stk[p].x == i)
		{
			printf("%lld\n", stk[p].y);
		}
		else
		{
			printf("%lld\n", (stk[p].y * (i - stk[p - 1].x) + stk[p - 1].y * (stk[p].x - i)) / (stk[p].x - stk[p - 1].x));
		}
	}
	return 0;
}