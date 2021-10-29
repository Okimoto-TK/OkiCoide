#include <cstdio>
#include <vector>
#include <algorithm>
int n;
char s[100005];
std::vector<int> pack;
std::vector<int> men;
int getDist(int l, int r, int x)
{
	if(l > x) return r - x;
	if(r < x) return x - l;
	return r - l + std::min(x - l, r - x);
}
bool check(int x)
{
	int ptr = 0;
	int size = pack.size();
	for(auto man : men)
	{
		int cnt = 0;
		while(ptr + cnt < size && getDist(pack[ptr], pack[ptr + cnt], man) <= x)
		{
			cnt++;
		}
		ptr += cnt;
	}
	return ptr == size;
}
int main()
{
	scanf("%d", &n);
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++)
	{
		if(s[i] == '*') pack.push_back(i);
		else if(s[i] == 'P') men.push_back(i);
	}
	int l = 1; int r = n + n / 2;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%d", l);
	return 0;
}
