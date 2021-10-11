#include <cstdio>
int w, b;
double f[3][1005][1005];
double dfs(int who, int _w, int _b)
{
	if(_w < 0 || _b < 0) return 0;
	if(_w == 0) return 0;
	if(_b == 0) return 2 - who;
	if(f[who][_w][_b] > 0) return f[who][_w][_b];
	if(who == 1)
	{
		f[who][_w][_b] = double(_w) / double(_w + _b) + double(_b) / double(_w + _b) * dfs(2, _w, _b - 1);
	}
	else
	{
		f[who][_w][_b] = double(_b) / double(_w + _b) * (double(_w) / double(_w + _b - 1) * dfs(1, _w - 1, _b - 1) + double(_b - 1) / double(_w + _b - 1) * dfs(1, _w, _b - 2));
	}
	return f[who][_w][_b];
}
int main()
{
	scanf("%d%d", &w, &b);
	printf("%.10lf", dfs(1, w, b));
	return 0;
}
