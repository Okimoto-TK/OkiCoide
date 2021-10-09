#include <cstdio>
#include <map>
#include <algorithm>
int n, ans;
int a[1005];
std::map<int, int> b;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[a[i]] += 1;
	}
	ans = std::max(2, b[0]);
	std::sort(a + 1, a + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == a[i - 1]) continue;
		for(int j = 1; j <= n; j++)
		{
			if(i == j) continue;
			if(a[i] == 0 && a[j] == 0) continue;
			std::map<int, int> t;
			t[a[i]]++;
			t[a[j]]++;
			int x = a[i];
			int y = a[j];
			int cnt = 2;
			while(b[x + y] > t[x + y])
			{
				t[x + y]++;
				int tmp = x + y;
				x = y;
				y = tmp;
				ans = std::max(ans, ++cnt);
			}
		}
	}
	printf("%d", ans);
	return 0;
}
