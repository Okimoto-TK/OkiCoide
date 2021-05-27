#include <stdio.h>
#include <algorithm>
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
int n;
int s[1007];
edge e[100007];
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
int main(int argc, char const *argv[])
{
    init();
    scanf("%d", &n);
    int p = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            int v;
            scanf("%d", &v);
            if(i == j){
                continue;
            }
            e[p].u = i;
            e[p].v = j;
            e[p ++].c = v;
        }
    }
    sort(e, e + n * (n - 1), cmp);
    int ans = 0;
    for(int i = 0; i < n * (n - 1); i ++){
        if(find(e[i].u) != find(e[i].v)){
            ans += e[i].c;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    printf("%d", ans);
    return 0;
}