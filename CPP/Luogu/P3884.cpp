#include <stdio.h>
#include <vector>
using namespace std;
struct node
{
    vector <int> vec;
    int dep;
};
node s[128];
int f[128][128];
int n;
int hrz[128];
int vrt;
int hrzt;
void swap(int & x, int & y){
    int t = x;
    x = y;
    y = t;
}
void preProc(int at, int super){
    s[at].dep = s[super].dep + 1;
    for(int i = 0; i <= 19; i ++)
        f[at][i + 1] = f[f[at][i]][i];
    for(int i = 0; i < s[at].vec.size(); i ++){
        int nxt = s[at].vec[i];
        if(nxt == super)
            continue;
        f[nxt][0] = at;
        preProc(nxt, at);
    }
}
int proc(int x, int y){
    if(s[x].dep < s[y].dep)
        swap(x, y);
    for(int i = 20; i >= 0; i --){
        if(s[f[x][i]].dep >= s[y].dep)
            x = f[x][i];
        if(x == y)
            return x;
    }
    for(int i = 20; i >= 0; i --){
        if(f[x][i] != f[y][i]){
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 1; i < n; i ++){
        int x, y;
        scanf("%d%d", &x, &y);
        s[x].vec.push_back(y);
        s[y].vec.push_back(x);
    }
    preProc(1, 0);
    for(int i = 1; i <= n; i ++){
        vrt = vrt > s[i].dep ? vrt : s[i].dep;
        hrz[s[i].dep] ++;
    }
    int u, v;
    scanf("%d%d", &u, &v);
    printf("%d\n", vrt)
    ;
    for(int i = 1; i <= 127; i ++)
        hrzt = hrzt > hrz[i] ? hrzt : hrz[i];
    printf("%d\n", hrzt);
    printf("%d\n", 2 * (s[u].dep - s[proc(u, v)].dep) + s[v].dep - s[proc(u,v)].dep);
    return 0;
}