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
vector <side> vct[1001];
vector <side> vct_[1001];
bool flg[1001];
bool flg_[1001];
int n, m, s;
int plot[1001];
int plot_[1001];
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
void dij_(int cnt){
	if(q.empty())
		return;
	if(cnt == n)
		return;
	node nd = q.top();
	int min = nd.ptr;
	while(flg_[min]){
		q.pop();
		nd = q.top();
		min = nd.ptr;
	}
	q.pop();
	flg_[min] = true;
	for(int i = 0; i < int(vct_[min].size()); i ++){
		if(plot_[min] + vct_[min][i].val < plot_[vct_[min][i].to]){
			plot_[vct_[min][i].to] = plot_[min] + vct_[min][i].val;
			if(!flg_[vct_[min][i].to]){
				node nd;
				nd.ptr = vct_[min][i].to;
				nd.val = plot_[nd.ptr];
				q.push(nd);
			}
		}
	}
	dij_(cnt + 1);
}
int main(int argc, char const *argv[])
{
	for(int i = 1; i < 1001; i ++)
		plot[i] = 2147483647;
	for(int i = 1; i < 1001; i ++)
		plot_[i] = 2147483647;
	scanf("%d %d", &n, &m);
	s = 1;
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
		temp.to = u;
		vct_[v].push_back(temp);
	}
	dij(0);
	plot_[s] = 0;
	nd.ptr = s;
	nd.val = 0;
	q.push(nd);
	dij_(0);
	int sum = 0;
	for(int i = 1; i <= n; i ++)
		sum += plot[i] + plot_[i];
	printf("%d", sum);
	return 0;
}