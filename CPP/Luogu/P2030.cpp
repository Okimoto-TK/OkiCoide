#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
int n, m;
char buf[256];
std::string name[10005];
bool check(std::string s, std::string t)
{
	if(t.length() > s.length()) return false;
	int l = t.length();
	for(int i = 0; i < l; i++)
	{
		if(s[i] != t[i]) return false;
	}
	return true;
}
bool half(std::string tar)
{
	int l = 1, r = n, mid;
	while(l < r)
	{
		mid = (l + r) >> 1;
		if(name[mid] >= tar)
			r = mid;
		else
			l = mid + 1;
	}
	return check(name[l], tar);
}
struct hInt
{
	int digit[600]; // 6-digit
	int len;
	hInt()
	{
		len = 0;
		memset(digit, 0, sizeof(digit));
	}
	void print()
	{
		if(len == 0)
		{
			printf("0");
			return;
		}
		for(int i = len; i >= 1; i--)
		{
			if(i != len)
			{
				int cnt = 0, x = digit[i];
				while(x != 0)
				{
					cnt++;
					x /= 10;
				}
				for(int j = 1; j <= 6 - cnt; j++)
				{
					printf("0");
				}
			}
			printf("%d", digit[i]);
		}
	}
	void operator+=(const hInt &a)
	{
		//print();
		//printf("+");
		/*
		if(len == 0)
		{
			printf("0");
		}
		else
		{
			for(int i = a.len; i >= 1; i--)
			{
				printf("%d", a.digit[i]);
			}
		}
		*/
		//printf("=");
		int max_len = std::max(len, a.len);
		bool cnt = false;
		for(int i = 1; i <= max_len; i++)
		{
			if(cnt)
			{
				digit[i]++;
				cnt = false;
			}
			digit[i] += a.digit[i];
			if(digit[i] >= 1000000)
			{
				digit[i] -= 1000000;
				cnt = true;
			}
		}
		len = max_len;
		if(cnt)
		{
			digit[++len] = 1;
		}
		//print();
		//printf(", len=%d\n", len);
	}
};
hInt f[2][2];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", buf);
		name[i] = buf;
	}
	std::sort(name + 1, name + 1 + n);
	int cnt = 0;
	for(int i = 1; i <= m; i++)
	{
		scanf("%s", buf);
		cnt += half(std::string(buf));
	}
	f[0][1].digit[1] = 1;
	f[0][1].len = 1;
	for(int i = 1; i <= n; i++)
	{
		//f[i ^ 1][0].print();
		//f[i ^ 1][1].print();
		f[i&1][1] = f[(i&1)^1][0];
		f[i&1][0] = f[(i&1)^1][0];
		f[i&1][0] += f[(i&1)^1][1];
		//f[i & 1][0].print();
		//f[i & 1][1].print();
	}
	f[n&1][0] += f[n&1][1];
	printf("%d\n", cnt);
	f[n&1][0].print();
	return 0;
}