#include <stdio.h>
using namespace std;
int n;
int m;
int sqr;
int rec;
int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < m; j ++){
			if(i == j)
				sqr += (n - i) * (m - j);
			else
				rec += (n - i) * (m - j);
		}
	}
	printf("%d %d", sqr, rec);
	return 0;
}