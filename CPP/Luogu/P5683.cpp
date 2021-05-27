#include <stdio.h>
#include <queue>
#include <vector>
#pragma GCC optimize(2)
using namespace std;
vector <int> v[3007];
int n, m;
int s1, t1, s2, t2;
struct point
{
	int idx;
	int val;
};
int dij(int start){
	queue <point> q;
	int tab[3007];
	for(int i = 0; i < 3007; i ++)
		tab[i] = 10000007;
	point tmp;
	tmp.val = 0;
	tmp.idx = start;
	q.push(tmp);
	tab[start] = 0;
	while(!q.empty()){
		point t = q.front();
		for(int i = 0; i < (int)v[t.idx].size(); i ++){
			if(tab[v[t.idx][i]] > t.val + 1){
				tab[v[t.idx][i]] = t.val + 1;
				tmp.val = t.val + 1;
				tmp.idx = v[t.idx][i];
				q.push(tmp);
			}
		}
		q.pop();
	}
	if(tab[1] + tab[s1] > t1 || tab[1] + tab[s2] > t2)
		return -1;
	return m - tab[1] - tab[s1] - tab[s2];
}
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++){
		int a, b;
		scanf("%d %d", &a, &b);
		v[a].push_back(b);
		v[b].push_back(a);
	}
	scanf("%d %d %d %d", &s1, &t1, &s2, &t2);
	int max = -1;
	for(int i = 1; i <= n; i ++){
		int t = dij(i);
		if(t > max)
			max = t;
	}
	printf("%d", max);
	return 0;
}