#include <cstdio>
#include <map>
int n;
int S[105];
std::map<int, int> mp;
long long ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &S[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		int a = S[i];
		for(int j = 1; j <= n; j++)
		{
			int b = S[j];
			for(int k = 1; k <= n; k++)
			{
				int c = S[k];
				mp[a * b + c] += 1;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		int d = S[i];
		if(d == 0) continue;
		for(int j = 1; j <= n; j++)
		{
			int e = S[j];
			for(int k = 1; k <= n; k++)
			{
				int f = S[k];
				ans += mp[d * (e + f)];
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
