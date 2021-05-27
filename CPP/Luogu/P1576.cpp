#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int INF = 10000000;
int n, m;
int to[200007];
double wt[200007];
double d[2007];
int p;
bool f[2007];
vector <int> vec[2007];
queue <int> q;
void qbbfa(int a){
    for(int i = 0; i < 2007; i ++)
        d[i] = INF;
    d[a] = 100;
    f[a] = true;
    q.push(a);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        f[u] = false;
        for(int i = 0; i < vec[u].size(); i ++){
            int v = to[vec[u][i]];
            double w = 1.00 / (1 - double(wt[vec[u][i]]) / 100.0);
            if(d[v] > d[u] * w){
                d[v] = d[u] * w;
                if(!f[v])
                    q.push(v);
            }
        }
    }
}
int a, b;
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        vec[x].push_back(p);
        to[p] = y;
        wt[p ++] = z;
        vec[y].push_back(p);
        to[p] = x;
        wt[p ++] = z;
    }
    scanf("%d%d", &a, &b);
    qbbfa(a);
    printf("%.8lf", d[b]);
    return 0;
}