#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct edge
{
    int u;
    int v;
    double c;
};
struct node{
    int x;
    int y;
};
bool cmp(edge a, edge b){
    return a.c < b.c;
}
int n, m;
int s[1007];
node nd[100007];
edge e[1000007];
int find(int a){
    if(a == s[a])
        return a;
    s[a] = find(s[a]);
    return s[a];
}
void init(){
    for(int i = 0; i < 1007; i ++)
        s[i] = i;
}
double getLen(int a, int b){
    return sqrt(pow(nd[a].x - nd[b].x, 2) + pow(nd[a].y - nd[b].y, 2));
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d%d", &nd[i].x, &nd[i].y);
    for(int i = 0; i < m; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        s[find(u)] = find(v);
    }
    int p = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            if(i == j)
                continue;
            e[p].u = i;
            e[p].v = j;
            e[p ++].c = getLen(i, j);
        }
    }
    sort(e, e + p, cmp);
    double ans = 0;
    for(int i = 0; i < p; i ++){
        if(find(e[i].u) != find(e[i].v)){
            ans += e[i].c;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    printf("%.2f", ans);
    return 0;
}