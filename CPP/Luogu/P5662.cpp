#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
	int t, n, m;
	scanf("%d %d %d\n", &t, &n, &m);
	int price[t + 100][n + 100];
	for(int i = 1; i <= t; i ++){
		for(int j = 1; j <= n; j ++){
			scanf("%d", &price[i][j]);
		}
	}
	for(int i = 2; i <= t; i ++){
		int pro[n + 100];
		for(int j = 1; j <= n; j ++){
			pro[j] = price[i][j] - price[i - 1][j];
		}
		int tab[m + 100];
		for(int j = 0; j <= m; j ++) tab[j] = 0;
		for(int y = 1; y <= n; y ++){
			for(int x = 1; x <= m; x ++){
				if(pro[y] < 0)
					continue;
				tab[x] = price[i - 1][y] > x ? tab[x] : (pro[y] + tab[x - price[i - 1][y]] > tab[x] ? pro[y] + tab[x - price[i - 1][y]] : tab[x]);
			}
		}
		m += tab[m];
	}
	printf("%d", m);
	return 0;
}
