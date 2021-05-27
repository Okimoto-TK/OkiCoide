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
int n, m;
int s[2007];
edge e[10007];
int find(int a){
    if(a == s[a])
        return a;
    s[a] = find(s[a]);
    return s[a];
}
void init(){
    for(int i = 0; i < 2007; i ++)
        s[i] = i;
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d", &n, &m);
    int sum = 0;
    for(int i = 0; i < m; i ++){
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        e[i].u = u;
        e[i].v = v;
        e[i].c = c;
        sum += c;
    }
    sort(e, e + m, cmp);
    int ans = 0;
    for(int i = 0; i < m; i ++){
        if(find(e[i].u) != find(e[i].v)){
            ans += e[i].c;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    printf("%d", sum - ans);
    return 0;
}