#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 500000
int n, c;
int a[N + 5];
int sum[N + 5];
std::vector<int> vec[N + 5];
int ans;
int main()
{
	scanf("%d%d", &n, &c);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + (a[i] == c ? 1 : 0);
		vec[a[i]].push_back(i);
	}
	for(int i = 1; i <= N; i++)
	{
		int max = 0;
		int val = 0;
		int last = 0;
		for(auto j : vec[i])
		{
			val -= sum[j - 1] - sum[last];
			if(val < 0) val = 0;
			val += 1;
			val -= sum[j] - sum[j - 1];
			max = std::max(max, val);
			last = j;
		}
		ans = std::max(ans, max);
	}
	printf("%d", ans + sum[n]);
	return 0;
}