#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct node
{
    int x;
    int y;
};
struct edge
{
    int u;
    int v;
    double c;
};
bool cmp(edge a, edge b){
    return a.c < b.c;
}
int n, m;
int s[2007];
int mk[1007];
node nd[1007];
edge e[1000007];
int find(int a){
    if(a == s[a])
        return a;
    s[a] = find(s[a]);
    return s[a];
}
double getLen(int a, int b){
    return sqrt(pow(nd[a].x - nd[b].x, 2) + pow(nd[a].y - nd[b].y, 2));
}
void init(){
    for(int i = 0; i < 2007; i ++)
        s[i] = i;
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d", &m);
    for(int i = 0; i < m; i ++){
        scanf("%d", &mk[i]);
    }
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        scanf("%d%d", &nd[i].x, &nd[i].y);
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
    int max = 0;
    for(int i = 0; i < p; i ++){
        if(find(e[i].u) != find(e[i].v)){
            max = e[i].c;
            s[find(e[i].u)] = find(e[i].v);
        }
    }
    int cnt = 0;
    for(int i = 0; i < m; i ++){
        if(max <= mk[i])
            cnt ++;
    }
    printf("%d\n", cnt);
    return 0;
}