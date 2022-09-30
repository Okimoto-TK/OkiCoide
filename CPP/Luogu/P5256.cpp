#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 1000000
int q;
int n, m;
char s[N + 5];
char t[N + 5];
int a[N + 5];
int b[N + 5];
int last[30];
int nxt[N + 5];
bool equal(int x, int y, int len)
{
	if(x < 0 || y < 0) return x == y;
	else return x == y || (y == 0 && x > len);
}
void kmp() {
	int j=0,ans=0; nxt[1]=0;
	for(int i=1;i<m;i++) {
		while(j&&!equal(b[i+1],b[j+1],j)) j=nxt[j];
		if(equal(b[i+1],b[j+1],j)) j++;
		nxt[i+1]=j;
	}
	j=0;
	for(int i=0;i<n;i++) {
		while(j&&!equal(a[i+1],b[j+1],j)) j=nxt[j];
		if(equal(a[i+1],b[j+1],j)) j++;
		if(j==m) ans++,j=nxt[j];
	}
	printf("%d\n",ans);
}
void solve()
{
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(s, 0, sizeof(s));
	memset(t, 0, sizeof(t));
	memset(last, 0, sizeof(last));
	memset(nxt, 0, sizeof(nxt));
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);
	for(int i = 1; i <= n; i++)
	{
		if('a' <= s[i] && s[i] <= 'z')
		{
			a[i] = (last[s[i] - 'a' + 1] == 0) ? 0 : i - last[s[i] - 'a' + 1];
			last[s[i] - 'a' + 1] = i;
		}
		else
		{
			a[i] = 'A' - s[i] - 1;
		}
	}
	memset(last, 0, sizeof(last));
	for(int i = 1; i <= m; i++)
	{
		if('a' <= t[i] && t[i] <= 'z')
		{
			b[i] = (last[t[i] - 'a' + 1] == 0) ? 0 : i - last[t[i] - 'a' + 1];
			last[t[i] - 'a' + 1] = i;
		}
		else
		{
			b[i] = 'A' - t[i] - 1;
		}
	}
	kmp();
}
int main()
{
	for(scanf("%d", &q); q; q--)
	{
		solve();
	}
}
