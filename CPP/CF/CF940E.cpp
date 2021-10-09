#include <cstdio>
#include <deque>
#include <algorithm>
struct Stamp
{
	int val;
	int time;
	Stamp()
	{
		val = time = 0;
	}
	Stamp(int a, int b)
	{
		val = a;
		time = b;
	}
};
int n, c;
int a[100005];
int val[100005];
long long sum;
long long f[100005];
std::deque<Stamp> q;
int main()
{
	scanf("%d%d", &n, &c);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		sum += a[i];
	}
	for(int i = 1; i <= c; i++)
	{
		while(!q.empty() && a[i] < q.back().val) q.pop_back();
		q.push_back(Stamp(a[i], i));
	}
	val[1] = q.front().val;
	for(int i = 2; i + c - 1 <= n; i++)
	{
		while(!q.empty() && q.front().time < i) q.pop_front();
		while(!q.empty() && a[i + c - 1] < q.back().val) q.pop_back();
		q.push_back(Stamp(a[i + c - 1], i + c - 1));
		val[i] = q.front().val;
	}
	f[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		f[i] = f[i - 1];
		if(i >= c) f[i] = std::max(f[i], f[i - c] + val[i - c + 1]);
	}
	printf("%lld", sum - f[n]);
	return 0;
}
