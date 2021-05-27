#include <stdio.h>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;
struct side
{
	int to;
	int val;
};
struct node
{
	int ptr;
	int val;
	bool operator <( const node &x )const
    {
        return x.val < val;
    }
};
priority_queue <node> q;
vector <side> vct[100001];
bool flg[100001];
int n, m, s;
int plot[100001];
void dij(int cnt){
	if(q.empty())
		return;
	if(cnt == n)
		return;
	node nd = q.top();
	int min = nd.ptr;
	while(flg[min]){
		q.pop();
		nd = q.top();
		min = nd.ptr;
	}
	q.pop();
	flg[min] = true;
	for(int i = 0; i < int(vct[min].size()); i ++){
		if(plot[min] + vct[min][i].val < plot[vct[min][i].to]){
			plot[vct[min][i].to] = plot[min] + vct[min][i].val;
			if(!flg[vct[min][i].to]){
				node nd;
				nd.ptr = vct[min][i].to;
				nd.val = plot[nd.ptr];
				q.push(nd);
			}
		}
	}
	dij(cnt + 1);
}
int main(int argc, char const *argv[])
{
	for(int i = 1; i < 100001; i ++)
		plot[i] = 2147483647;
	scanf("%d %d %d", &n, &m, &s);
	plot[s] = 0;
	node nd;
	nd.ptr = s;
	nd.val = 0;
	q.push(nd);
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