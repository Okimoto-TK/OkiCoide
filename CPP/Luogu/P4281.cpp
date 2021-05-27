#include <stdio.h>
#include <vector>
using namespace std;
struct node
{
    vector <int> vec;
    int dep;
};
node s[500007];
int f[500007][30];
int n, m;
void pre_proc(int at, int super){
    s[at].dep = s[super].dep + 1;
    for(int i = 0; i < 20; i ++)
        f[at][i + 1] = f[f[at][i]][i];
    for(int i = 0; i < s[at].vec.size(); i ++){
        int nxt = s[at].vec[i];
        if(nxt == super)
            continue;
        f[nxt][0] = at;
        pre_proc(nxt, at);
    }
}
void swap(int & x, int & y){
    int t = x;
    x = y;
    y = t;
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
int abs(int x){
    return x > 0 ? x : -x;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        s[a].vec.push_back(b);
        s[b].vec.push_back(a);
    }
    pre_proc(1, 0);
    for(int i = 1; i <= m; i ++){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int xy = proc(x, y);
        int xz = proc(x, z);
        int yz = proc(y, z);
        int ans = s[xy].dep > s[xz].dep ? (s[xy].dep > s[yz].dep ? xy : (s[xz].dep > s[yz].dep ? xz : yz)) : (s[xz].dep > s[yz].dep ? xz : (s[xy].dep > s[yz].dep ? xy : yz));
        int cst = 0;
        int xa = proc(ans, x);
        int ya = proc(ans, y);
        int za = proc(ans, z);
        cst += (s[ans].dep - s[xa].dep + s[x].dep - s[xa].dep);
        cst += (s[ans].dep - s[ya].dep + s[y].dep - s[ya].dep);
        cst += (s[ans].dep - s[za].dep + s[z].dep - s[za].dep);
        printf("%d %d\n", ans, cst);
    }
    return 0;
}