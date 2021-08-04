#include <cstdio>
#include <algorithm>
// Sample
//       01    02
//       03    04
// 05 06 07 08 09 10 11
//       12    13
// 14 15 16 17 18 19 20
//       21    22
//       23    24
int a[30];
const int ctr[8] = {7, 8, 9, 12, 13, 16, 17, 18};
const int opr[2][2][7] = {{{23, 21, 16, 12, 7, 3, 1}, {24, 22, 18, 13, 9, 4, 2}}, {{5, 6, 7, 8, 9, 10, 11}, {14, 15, 16, 17, 18, 19, 20}}}; // 1. col 2.row
const char tar[2][2][2] = {{{'A', 'F'}, {'B', 'E'}}, {{'C', 'H'}, {'D', 'G'}}};
int count()
{
	int cnt[4] = {0, 0, 0, 0};
	for(int i = 0; i <= 7; i++)
	{
		cnt[a[ctr[i]]]++;
	}
	return 8 - std::max(std::max(cnt[1], cnt[2]), cnt[3]);
}
void change(int roc, int wch, bool opp)
{
	if(!opp)
	{
		int tmp = a[opr[roc][wch][6]];
		for(int i = 6; i >= 1; i--)
		{
			a[opr[roc][wch][i]] = a[opr[roc][wch][i - 1]];
		}
		a[opr[roc][wch][0]] = tmp;
	}
	else
	{
		int tmp = a[opr[roc][wch][0]];
		for(int i = 0; i <= 5; i++)
		{
			a[opr[roc][wch][i]] = a[opr[roc][wch][i + 1]];
		}
		a[opr[roc][wch][6]] = tmp;
	}
}
int limit;
char ans[100];
bool dfs(int dep, int lasti, int lastj, int lastk)
{
	if(count() == 0) return true;
	if(dep == limit) return false;
	for(int i = 0; i <= 1; i++)
	{
		for(int j = 0; j <= 1; j++)
		{
			int k = 0;
			if(i == lasti && j == lastj && k != lastk) continue;
			change(i, j, k == 1);
			ans[dep] = tar[i][j][k];
			if(dep + count() <= limit) if(dfs(dep + 1, i, j, k)) return true;
			change(i, j, k == 0);
		}

	}
	for(int i = 0; i <= 1; i++)
	{
		for(int j = 1; j >= 0; j--)
		{
			int k = 1;
			if(i == lasti && j == lastj && k != lastk) continue;
			change(i, j, k == 1);
			ans[dep] = tar[i][j][k];
			if(dep + count() <= limit) if(dfs(dep + 1, i, j, k)) return true;
			change(i, j, k == 0);
		}
	}
	return false;
}
int main()
{
	for(scanf("%d", &a[1]); a[1] != 0; scanf("%d", &a[1]))
	{
		for(int i = 2; i <= 24; i++) scanf("%d", &a[i]);
		limit = 0;
		while(!dfs(0, -1, -1, -1)) limit++;
		if(limit == 0) printf("No moves needed");
		else for(int i = 0; i < limit; i++) printf("%c", ans[i]);
		putchar('\n');
		printf("%d\n", a[ctr[0]]);
	}
	return 0;
}
