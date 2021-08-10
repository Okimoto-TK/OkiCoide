#include <cstdio>
#include <cstring>
#define MAX_LIMIT 5
int a[4][4];
int b[4][4];
int t[4][4];
void change(int op)
{
	if(op == 1)
	{
		t[1][1] = a[3][1];
		t[1][2] = a[2][1];
		t[1][3] = a[1][1];
		t[2][1] = a[3][2];
		t[2][2] = a[2][2];
		t[2][3] = a[1][2];
		t[3][1] = a[3][3];
		t[3][2] = a[2][3];
		t[3][3] = a[1][3];
	}
	else if(op == 2)
	{
		t[3][1] = a[1][1];
		t[2][1] = a[1][2];
		t[1][1] = a[1][3];
		t[3][2] = a[2][1];
		t[2][2] = a[2][2];
		t[1][2] = a[2][3];
		t[3][3] = a[3][1];
		t[2][3] = a[3][2];
		t[1][3] = a[3][3];
	}
	else if(op == 4)
	{
		t[1][1] = a[3][1];
		t[1][2] = a[3][2];
		t[1][3] = a[3][3];
		t[3][3] = a[1][3];
		t[3][2] = a[1][2];
		t[3][1] = a[1][1];
	}
	else
	{
		t[1][1] = a[1][3];
		t[2][1] = a[2][3];
		t[3][1] = a[3][3];
		t[1][3] = a[1][1];
		t[2][3] = a[2][1];
		t[3][3] = a[3][1];
	}
	for(int i = 1; i <= 3; i++)
	{
		for(int j = 1; j <= 3; j++)
		{
			a[i][j] = t[i][j];
		}
	}
}
bool check()
{
	for(int i = 1; i <= 3; i++)
	{
		for(int j = 1; j <= 3; j++)
		{
			if(a[i][j] != b[i][j]) return false;
		}
	}
	return true;
}
int limit;
int ans[10];
bool dfs(int dep)
{
	if(check())	return true;
	if(dep == limit) return false;
	for(int i = 1; i <= 4; i++)
	{
		change(i);
		ans[dep] = i;
		if(dfs(dep + 1)) return true;
		change(i == 1 ? 2 : (i == 2 ? 1 : i));
	}
	return false;
}
int main()
{
	for(int i = 1; i <= 3; i++)
	{
		for(int j = 1; j <= 3; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
	for(int i = 1; i <= 3; i++)
	{
		for(int j = 1; j <= 3; j++)
		{
			scanf("%d", &b[i][j]);
		}
	}
	while(limit <= MAX_LIMIT && !dfs(0)) limit++;
	if(limit == 0)
	{
		printf("AB");
	}
	else if(limit > MAX_LIMIT) printf("Poland cannot into space!!!");
	else
	{
		for(int i = 0; i < limit; i++) printf("%c", ans[i] - 1 + 'A');
	}
	return 0;
}
