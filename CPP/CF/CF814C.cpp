#include <cstdio>
#include <cstring>
int n, q;
char s[1505];
int cnt[26][1505];
bool check(int x, int m, char c)
{
	for(int l = 1; l + x - 1 <= n; l++)
	{
		int r = l + x - 1;
		if(x - (cnt[c - 'a'][r] - cnt[c - 'a'][l - 1]) <= m) return true;
	}
	return false;
}
int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < 26; j++)
		{
			cnt[j][i] = cnt[j][i - 1];
		}
		cnt[s[i] - 'a'][i]++;
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int m;
		char buf[2];
		scanf("%d%s", &m, buf);
		char c = buf[0];
		int l = 0;
		int r = n;
		while(l < r)
		{
			int mid = (l + r + 1) >> 1;
			if(check(mid, m, c)) l = mid;
			else r = mid - 1;
		}
		printf("%d\n", l);
	}
	return 0;
}
