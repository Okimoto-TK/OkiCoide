#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
int n, m, s, t;
std::vector<int> g[10005];
std::vector<int> _g[10005];
inline void AddEdge(int u, int v) {
	if(u == v) return;
	g[u].push_back(v);
	_g[v].push_back(u);
}
bool vld[10005];
inline void ChkVld() {
	std::queue<int> q;
	q.push(t);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		vld[u] = true;
		for(auto v : _g[u]) {
			if(!vld[v]) q.push(v);
		}
	}
}
inline void ReChk() {
	std::queue<int> q;
	for(int i = 1; i <= n; i++) {
		if(!vld[i]) q.push(i);
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(auto v : _g[u]) {
			if(vld[v])
			{
				vld[v] = false;
			}
		}
	}
}
inline int Dijkstra() {
	int dis[10005];
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > heap;
	heap.push(std::make_pair(s, 0));
	dis[s] = 0;
	while(!heap.empty()) {
		int u = heap.top().first;
		int d = heap.top().second;
		heap.pop();
		if(dis[u] < d) continue;
		for(auto v : g[u]) {
			if(!vld[v]) continue;
			if(dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				heap.push(std::make_pair(v, dis[v]));
			}
		}
	}
	return dis[t];
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	scanf("%d%d", &s, &t);
	ChkVld();
	ReChk();
	if(!vld[s]) {
		printf("-1");
		return 0;
	}
	int ans = Dijkstra();
	printf("%d", ans >= 0x3f3f3f3f ? -1 : ans);
	return 0;
}
