#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;
struct edge
{
    int u;
    int v;
    int c;
};
bool cmp(edge a, edge b){
    return a.c < b.c;
}
int n, p;
int s[10007];
int ans[10007];
edge e[20007];
bool been[10007];
vector < pair<int, int> > v[10007];
int find(int a){
    if(a == s[a])
        return a;
    s[a] = find(s[a]);
    return s[a];
}
void init(){
    for(int i = 0; i < 10007; i ++)
        s[i] = i;
}
int getMax(int a, int b){
    return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
    init();
    int _s;
    int _t;
    scanf("%d%d%d%d", &n, &p, &_s, &_t);
    for(int i = 0; i < p; i ++){
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].c);
    }
    sort(e, e + p, cmp);
    for(int i = 0; i < p; i ++){
        if(find(e[i].u) != find(e[i].v)){
            v[e[i].u].push_back(pair<int, int>(e[i].v, e[i].c));
            v[e[i].v].push_back(pair<int, int>(e[i].u, e[i].c));
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    queue <int> q;
    q.push(_s);
    while(!q.empty()){
        int at = q.front();
        for(int i = 0; i < v[at].size(); i ++){
            if(!been[v[at][i].first]){
                been[v[at][i].first] = true;
                q.push(v[at][i].first);
                ans[v[at][i].first] = getMax(ans[at], v[at][i].second);
            }
        }
        q.pop();
    }
    printf("%d\n", ans[_t]);
    return 0;
}