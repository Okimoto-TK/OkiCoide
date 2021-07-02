// Inc
#include <cstdio>
#include <cstring>
#include <string>

// Var
int p, k;
std::string st;
int s;
std::string t[10];
int f[205][30];
bool vis[205];
int pre[10][205];
int len[10];
int xxx[10];
// Func.getPre <- [main]
void getPre()
{
	for(int i = 1; i <= s; i++)
	{
		len[i] = t[i].size();
		int x = 0;
		for(int j = 1; j < len[i]; j++)
		{
			while(x != 0 && t[i][x] != t[i][j]) x = pre[i][x];
			pre[i][j + 1] = t[i][x] == t[i][j] ? ++x : 0;
		}		
	}
}
// Func.kmp <- [main]
int kmp(int l, int r)
{
	// Func.kmp -> init
	int res = 0;
	memset(vis, 0, sizeof(vis));
	memset(xxx, 0, sizeof(xxx));

	// Func.kmp -> dp
	for(int i = l; i <= r; i++)
	{
		for(int j = 1; j <= s; j++)
		{
			while(xxx[j] != 0 && st[i] != t[j][xxx[j]]) xxx[j] = pre[j][xxx[j]];
			if(st[i] == t[j][xxx[j]]) xxx[j]++;
			if(xxx[j] == len[j] && !vis[i - len[j] + 1])
			{
				vis[i - len[j] + 1] = true;
				res++;
			}
		}
	}
	return res;
}

// Func.main <- *
int main()
{
	// Func.main -> input
	scanf("%d%d", &p, &k);
	for(int i = 1; i <= p; i++)
	{
		char buf[25];
		scanf("%s", buf);
		st += buf;
	}
	scanf("%d", &s);
	for(int i = 1; i <= s; i++)
	{
		char buf[25];
		scanf("%s", buf);
		t[i] = buf;
	}	
	// Func.main -> Func.getPre
	getPre();
	
	// Func.main -> dp -> [Func.kmp]
	for(int i = 0; i < p * 20; i++)
	{
		for(int j = 1; j <= k; j++)
		{
			if(j != 1)
			{
				for(int _i = 0; _i < i; _i++)
				{
					if(f[_i][j - 1] != 0) f[i][j] = std::max(f[i][j], f[_i][j - 1] + kmp(_i + 1, i));
				}
			}
			else f[i][j] = kmp(0, i);
		}
	}
	
	// Func.main -> output
	printf("%d", f[p * 20 - 1][k]);
	return 0;
}
