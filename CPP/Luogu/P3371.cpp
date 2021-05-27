#include <stdio.h>
#include <vector>
using namespace std;
struct side
{
	int to;
	int val;
};
vector <side> vct[10001];
int n, m, s;
bool flg[10001];
int plot[10001];
void dij(int cnt){
	if(cnt == n)
		return;
	int min;
	int mvl = 100000000;
	for(int i = 1; i <= n; i ++){
		if(plot[i] < mvl && (!flg[i])){
			mvl = plot[i];
			min = i;
		}
	}
	for(int i = 0; i < vct[min].size(); i ++){
		if(plot[min] + vct[min][i].val < plot[vct[min][i].to]){
			plot[vct[min][i].to] = plot[min] + vct[min][i].val;
		}
	}
	flg[min] = true;
	dij(cnt + 1);
}
int main(int argc, char const *argv[])
{
	for(int i = 1; i < 10001; i ++)
		plot[i] = 2147483647;
	scanf("%d %d %d", &n, &m, &s);
	plot[s] = 0;
	for(int i = 0; i < m; i ++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		side temp;
		temp.to = v;
		temp.val = w;
		vct[u].push_back(temp);
	}
	dij(0);
	for(int i = 1; i <= n; i ++){
		printf("%d ", plot[i]);
	}
	return 0;
}