#include <cstdio>
long long basis[100];
int tot;
void insert(long long x)
{
	for(int d = 51; d >= 0; d--)
	{
		if(x & (1ll << d))
		{
			if(basis[d] == 0)
			{
				basis[d] = x;
				tot++;
				break;
			}
			else
			{
				x ^= basis[d];
			}
		}
	}
}
long long query()
{
	long long ans = 0;
	for(int d = 51; d >= 0; d--)
	{
		if((ans ^ basis[d]) > ans)
		{
			ans ^= basis[d];
		}
	}
	return ans;
}
long long a[100];
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		insert(a[i]);
	}
	printf("%lld", query());
}