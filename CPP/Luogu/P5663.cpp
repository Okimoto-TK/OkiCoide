#include <stdio.h>
#include <vector>
#include <queue>
#define INF 100000000
using namespace std;
struct node
{
	int e = INF;
	int o = INF;
};
int main(int argc, char const *argv[])
{
	int n, m, q;
	node num[100110];
	vector <int> vec[100110];
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 0; i < m; i ++){
		int u, v;
		scanf("%d %d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	queue <int> que;
	num[1].e = 0;
	que.push(1);
	while(que.size() != 0){
		for(unsigned long long i = 0; i < vec[que.front()].size(); i ++){
			if((num[que.front()].o + 1) % 2 == 0 && num[vec[que.front()][i]].e > num[que.front()].o + 1){
				que.push(vec[que.front()][i]);
				num[vec[que.front()][i]].e = num[que.front()].o + 1;
			}
			if((num[que.front()].e + 1) % 2 == 1 && num[vec[que.front()][i]].o > num[que.front()].e + 1){
				que.push(vec[que.front()][i]);
				num[vec[que.front()][i]].o = num[que.front()].e + 1;
			}
		}
		que.pop();
	}
	queue <bool> ans;
	for(int i = 0; i < q; i ++){
		int a, l;
		scanf("%d %d", &a, &l);
		if(l % 2 == 0 && num[a].e <= l){
			ans.push(true);
			continue;
		}
		if(l % 2 == 1 && num[a].o <= l){
			ans.push(true);
			continue;
		}
		ans.push(false);
	}
	while(ans.size() != 0){
		if(ans.front()) printf("Yes\n");
		else printf("No\n");
		ans.pop();
	}
	return 0;
}