#include <stdio.h>
#include <vector>
using namespace std;
struct node
{
    vector <int> vec;
    int dep;
};
node tree[500007];
int f[500007][32];
int n, m, s;
void swap(int & x, int & y){
    int t = x;
    x = y;
    y = t;
}
void pre_proc(int at, int super){
    tree[at].dep = tree[super].dep + 1;
    for(int i = 0; i <= 19; i ++)
        f[at][i + 1] = f[f[at][i]][i];
    for(int i = 0; i < tree[at].vec.size(); i ++){
        int v = tree[at].vec[i];
        if(v == super)
            continue;
        f[v][0] = at;
        pre_proc(v, at);
    }
}
int proc(int x, int y){
    if(tree[x].dep < tree[y].dep)
        swap(x, y);
    for(int i = 20; i >= 0; i --){
        if(tree[f[x][i]].dep >= tree[y].dep)
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
    scanf("%d%d%d", &n, &m, &s);
    for(int i = 1; i <= n - 1; i ++){
        int x, y;
        scanf("%d%d", &x, &y);
        tree[x].vec.push_back(y);
        tree[y].vec.push_back(x);
    }
    f[s][0] = 0;
    tree[s].dep = 1;
    for(int i = 0; i < tree[s].vec.size(); i ++){
        f[tree[s].vec[i]][0] = s;
        pre_proc(tree[s].vec[i], s);
    }
    for(int i = 0; i < m; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", proc(a, b));
    }
    return 0;
}