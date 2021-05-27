#include <stdio.h>
#include <algorithm>
using namespace std;
struct edge
{
    int u;
    int v;
    long long c;
};
bool cmp(edge a, edge b){
    return a.c > b.c;
}
int n, m;
long long x[2007];
int s[2007];
edge e[4000007];
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
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
        scanf("%lld", &x[i]);
    int p = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            if(i == j)
                continue;
            e[p].u = i;
            e[p].v = j;
            e[p ++].c = x[i] ^ x[j];
        }
    }
    sort(e, e + p, cmp);
    long long ans = 0;
    for(int i = 0; i < p; i ++){
        if(find(e[i].u) != find(e[i].v)){
            ans += e[i].c;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    printf("%lld", ans);
    return 0;
}