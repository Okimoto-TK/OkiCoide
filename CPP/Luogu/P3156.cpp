#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
vector <int> v;
queue <int> q;
int main(int argc, char const *argv[])
{
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i ++){
		int in;
		scanf("%d", &in);
		v.push_back(in);
	}
	for(int i = 0; i < m; i ++){
		int qs;
		scanf("%d", &qs);
		q.push(v[qs - 1]);
	}
	while(!q.empty()){
		printf("%d\n", q.front());
		q.pop();
	}
	return 0;
}