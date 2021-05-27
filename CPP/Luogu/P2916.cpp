#include <stdio.h>
#include <algorithm>
#include <math.h>
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
int n, p, m = 0x3f3f3f3f;
int s[10007];
int c[10007];
edge e[100007];
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
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d", &n, &p);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &c[i]);
        m = m < c[i] ? m : c[i];
    }
    for(int i = 0; i < p; i ++){
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].c);
        e[i].c *= 2;
        e[i].c += c[e[i].u] + c[e[i].v];
    }
    sort(e, e + p, cmp);
    int ans = 0;
    for(int i = 0; i < p; i ++){
        if(find(e[i].u) != find(e[i].v)){
            ans += e[i].c;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    printf("%d\n", ans + m);
    return 0;
}