#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int T;
char str[200005];
struct clo
{
	int len, typ;
} q[200005];
bool cmp(clo a, clo b)
{
	return a.len < b.len;
}
// 0: AB
// 1: BA
int cnta, cntb;
bool solve()
{
	int cntab = 0;
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	scanf("%s", str + 1);
	int len = strlen(str + 1);
	int l = 1;
	int cnt = 0;
	//printf("%c", str[1]);
	for(int i = 2; i <= len; i++)
	{
		if(str[i] == str[i - 1])
		{
			//printf("|");
			if(l == i - 1)
			{
				if(str[i - 1] == 'A')
				{
					if(--a < 0) return false;
				}
				else
				{
					if(--b < 0) return false;
				}
			}
			else
			{
				if(str[l] == 'A' && str[i - 1] == 'B')
				{
					q[++cnt].len = i - l;
					q[cnt].typ = 0;
				}
				else if(str[l] == 'B' && str[i - 1] == 'A')
				{
					q[++cnt].len = i - l;
					q[cnt].typ = 1;
				}
				else if(str[l] == 'A' && str[i - 1] == 'A')
				{
					if(--a < 0) return false;
					cntab += (i - l - 1) / 2;
				}
				else
				{
					if(--b < 0) return false;
					cntab += (i - l - 1) / 2;
				}
			}
			l = i;
		}
		//printf("%c", str[i]);
	}
	if(l == len)
	{
		if(str[len] == 'A')
		{
			if(--a < 0) return false;
		}
		else
		{
			if(--b < 0) return false;
		}
	}
	else
	{
		if(str[l] == 'A' && str[len] == 'B')
		{
			q[++cnt].len = len - l + 1;
			q[cnt].typ = 0;
		}
		else if(str[l] == 'B' && str[len] == 'A')
		{
			q[++cnt].len = len - l + 1;
			q[cnt].typ = 1;
		}
		else if(str[l] == 'A' && str[len] == 'A')
		{
			if(--a < 0) return false;
			cntab += (len - l) / 2;
		}
		else
		{
			if(--b < 0) return false;
			cntab += (len - l) / 2;
		}
	}
	std::sort(q + 1, q + 1 + cnt, cmp);
	for(int i = 1; i <= cnt; i++)
	{
		if(q[i].typ == 0)
		{
			if(c >= q[i].len / 2)
			{
				c -= q[i].len / 2;
				q[i].len = 0;
			}
			else
			{
				q[i].len -= c * 2;
				c = 0;
			}
			if(c == 0 && q[i].len > 0)
			{
				if(--a < 0) return false;
				if(--b < 0) return false;
				q[i].len -= 2;
				if(q[i].len > 0)
				{
					cntab += q[i].len / 2;
				}
			}
		}
		else
		{
			if(d >= q[i].len / 2)
			{
				d -= q[i].len / 2;
				q[i].len = 0;
			}
			else
			{
				q[i].len -= d * 2;
				d = 0;
			}
			if(d == 0 && q[i].len > 0)
			{
				if(--a < 0) return false;
				if(--b < 0) return false;
				q[i].len -= 2;
				if(q[i].len > 0)
				{
					cntab += q[i].len / 2;
				}
			}
		}
	}
	//printf("::%d %d %d %d %d\n", a, b, c, d, cntab);
	return (a + c + d == cntab) && (b + c + d == cntab);
}
int main()
{
	for(scanf("%d", &T); T; T--)
	{
		printf("%s\n", solve() ? "YES" : "NO");
	}
}
