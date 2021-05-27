#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
struct edge
{
    int a;
    int b;
    int wt;
};
edge e[250007];
int s[1007];
bool cmp(edge a, edge b){
    return a.wt < b.wt;
}
void init(){
    for(int i = 0; i < 1007; i ++)
        s[i] = i;
}
int find(int x){
    if(s[x] == x)
        return x;
    else{
        int r = find(s[x]);
        s[x] = r;
        return r;
    }
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d", &m, &n);
    int p = 0;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++){
            scanf("%d", &e[p].wt);
            if(e[p].wt >= m)
                e[p].wt = m;
            if(e[p].wt == 0)
                e[p].wt = m;
            e[p].a = i;
            e[p ++].b = j;
        }
    sort(e, e + p, cmp);
    int sum = 0;
    for(int i = 0; i < p; i ++){
        if(find(e[i].a) == find(e[i].b)){
            continue;
        }
        s[find(e[i].a)] = find(e[i].b);
        sum += e[i].wt;
    }
    printf("%d", sum + m);
    return 0;
}