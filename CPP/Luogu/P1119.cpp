#include <stdio.h>
using namespace std;
const int INF = 1e8;
int n, m, q;
int t[202];
int w[202][202];
int d[202][202][202];
int min(int a, int b){
	return a < b ? a : b;
}
int srch(int a){
	int p = 1;
	while(p <= n && t[p] <= a)
		p ++;
	return p - 1;
}
void init(){
	for(int i = 0; i < 256; i ++)
		for(int j = 0; j < 256; j ++){
			if(i == j)
				continue;
			w[i][j] = INF;
		}
}
int main(int argc, char const *argv[])
{
	init();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &t[i]);
	for(int i = 0; i < m; i ++){
		int u, v, _w;
		scanf("%d%d%d", &u, &v, &_w);
		w[u + 1][v + 1] = _w;
		w[v + 1][u + 1] = _w;
	}
	for(int i = 0; i < 202; i ++)
		for(int j = 0; j < 202; j ++)
			d[i][j][0] = w[i][j];
	for(int k = 1; k <= n; k ++)
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++){
				if(i == j)
					continue;
				d[i][j][k] = min(d[i][k][k - 1] + d[k][j][k - 1], d[i][j][k - 1]);
			}
	scanf("%d", &q);
	for(int i = 0; i < q; i ++){
		int x, y, _t;
		scanf("%d%d%d", &x, &y, &_t);
		int t_ = srch(_t);
		if(t_ < x + 1 || t_ < y + 1){
			printf("-1\n");
			continue;
		}
		printf("%d\n", d[x + 1][y + 1][t_] == INF ? -1 : d[x + 1][y + 1][t_]);
	}
	return 0;
}