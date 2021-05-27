#include <stdio.h>
using namespace std;
int it[5002][1100];
void add(int x){
	for(int i = 1099; i >= 0; i --){
		it[x][i] = it[x - 1][i];
	}
	int ptr = 1099;
	int upd = 0;
	while(ptr != 0){
		int sum = it[x][ptr] + it[x - 2][ptr] + upd;
		it[x][ptr] = sum % 10;
		upd = sum / 10;
		ptr --;
	}
	return;
}
int main(int argc, char const *argv[])
{
	int n, m;
	scanf("%d %d", &m, &n);
	n -= m - 1;
	if(n == 0){
		printf("0");
		return 0;
	}
	if (n == 1){
		printf("1");
		return 0;
	}
	if(n == 2){
		printf("2");
		return 0;
	}
	it[0][1099] = 0;
	it[1][1099] = 1;
	it[2][1099] = 1;
	for(int i = 3; i <= n; i ++){
		add(i);
	}
	bool flg = true;
	for(int i = 0; i < 1100; i ++){
		if(it[n][i] == 0 && flg){
			continue;
		}
		flg = false;
		printf("%d", it[n][i]);
	}
	return 0;
}