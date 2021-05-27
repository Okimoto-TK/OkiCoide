#include <stdio.h>
#include <algorithm>
using namespace std;
struct edge
{
    int u;
    int v;
    int c;
};
struct node
{
    int x;
    int y;
};
bool cmp(edge a, edge b){
    return a.c < b.c;
}
int n, c;
int s[2007];
node x[2007];
edge e[2000007];
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
int pow2(int a){
    return a * a;
}
int getLen(int a, int b){
    return pow2(x[a].x - x[b].x) + pow2(x[a].y - x[b].y);
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d", &n, &c);
    for(int i = 1; i <= n; i ++)
        scanf("%d%d", &x[i].x, &x[i].y);
    int p = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j < i; j ++){
            e[p].u = i;
            e[p].v = j;
            e[p].c = getLen(i, j);
            if(e[p].c >= c)
                p ++;
        }
    }
    sort(e, e + p, cmp);
    long long ans = 0;
    int cnt = 0;
    for(int i = 0; i < p; i ++){
        if(find(e[i].u) != find(e[i].v)){
            ans += e[i].c;
            cnt ++;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    if(cnt != n - 1)
        printf("-1");
    else
        printf("%lld", ans);
    return 0;
}