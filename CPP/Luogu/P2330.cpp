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
int n, m;
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
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].c);
    sort(e, e + m, cmp);
    int cnt = 0;
    int max = 0;
    for(int i = 0; i < m; i ++){
        if(find(e[i].u) != find(e[i].v)){
            cnt ++;
            max = e[i].c;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    printf("%d %d\n", cnt, max);
    return 0;
}