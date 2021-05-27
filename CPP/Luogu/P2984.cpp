#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
int n, m, b;
int d[50007];
bool f[50007];
int to[200007];
int wt[200007];
int p;
vector <int> vec[50007];
queue <int> q;
void qbbfa(){
    memset(d, 0x3f, sizeof(d));
    memset(f, 0, sizeof(f));
    d[1] = 0;
    f[1] = true;
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        f[u] = false;
        for(int i = 0; i < vec[u].size(); i ++){
            int v = to[vec[u][i]];
            int w = wt[vec[u][i]];
            if(d[v] > d[u] + w){
                d[v] = d[u] + w;
                if(!f[v]){
                    q.push(v);
                    f[v] = true;
                }
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    scanf("%d%d%d", &n, &m, &b);
    for(int i = 0; i < m; i ++){
        int r, s, l;
        scanf("%d%d%d", &r, &s, &l);
        vec[r].push_back(p);
        to[p] = s;
        wt[p ++] = l;
        vec[s].push_back(p);
        to[p] = r;
        wt[p ++] = l;
    }
    qbbfa();
    for(int i = 0; i < b; i ++){
        int _p, _q;
        scanf("%d%d", &_p, &_q);
        printf("%d\n", d[_p] + d[_q]);
    }
    return 0;
}