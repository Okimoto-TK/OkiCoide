#include <cstdio>
#include <string>
#include <map>
int n, m, q;
int s[200005];
char bf[30];
std::map<std::string, int> mapIdx;
int find(int x)
{
	if(s[x] == x) return x;
	return s[x] = find(s[x]);
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= 2 * n; i++) s[i] = i;
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", bf);
		std::string strBf = bf;
		mapIdx[strBf] = i;
	}
	for(int i = 1; i <= m; i++)
	{
		int rel;
		scanf("%d%s", &rel, bf);
		std::string strA = bf;
		int a = mapIdx[strA];
		scanf("%s", bf);
		std::string strB = bf;
		int b = mapIdx[strB];
		if(rel == 1)
		{
			if(find(a) == find(b + n) || find(b) == find(a + n))
			{
				printf("NO\n");
				continue;
			}
			s[find(b)] = find(a);
			s[find(b + n)] = find(a + n);
		}
		else
		{
			if(find(a) == find(b) || find(a + n) == find(b + n))
			{
				printf("NO\n");
				continue;
			}
			s[find(b + n)] = find(a);
			s[find(b)] = find(a + n);
		}
		printf("YES\n");
	}
	for(int i = 1; i <= q; i++)
	{
		scanf("%s", bf);
		std::string strA = bf;
		int a = mapIdx[strA];
		scanf("%s", bf);
		std::string strB = bf;
		int b = mapIdx[strB];
		if(find(a) == find(b)) printf("1\n");
		else if(find(a) == find(b + n) || find(b) == find(a + n)) printf("2\n");
		else printf("3\n");
	}
	return 0;
}
