#include <stdio.h>
#include <string.h>
#include <vector>
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
int n, w;
int s[207];
vector <edge> ev;
int find(int a){
    if(a == s[a])
        return a;
    s[a] = find(s[a]);
    return s[a];
}
void init(){
    for(int i = 0; i < 207; i ++)
        s[i] = i;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &w);
    for(int i = 0; i < w; i ++){
        int ans = 0;
        int cnt = 0;
        edge e;
        init();
        scanf("%d%d%d", &e.u, &e.v, &e.c);
        auto j = ev.begin();
        for(; j != ev.end(); j ++){
            if((*j).c > e.c)
                break;
        }
        ev.insert(j, e);
        for(int j = 0; j < (int)ev.size(); j ++){
            if(find(ev[j].u) != find(ev[j].v)){
                ans += ev[j].c;
                cnt ++;
                s[find(ev[j].u)] = find(ev[j].v);
            }
        }
        if(cnt != n - 1)
            printf("-1\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}