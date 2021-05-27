#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;
struct node
{
    int x;
    int y;
};
int n, m, s, t;
int to[2007];
double wt[2007];
double d[128];
bool f[2007];
node shp[128];
vector <int> vec[128];
int p;
queue <int> q;
double getLen(int x, int y){
    return sqrt(pow(shp[x].x - shp[y].x, 2) + pow(shp[x].y - shp[y].y, 2));
}
void qbbfa(){
    for(int i = 0; i < 128; i ++)
        d[i] = 100000000;
    d[s] = 0;
    f[s] = true;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        f[u] = false;
        for(int i = 0; i < vec[u].size(); i ++){
            int v = to[vec[u][i]];
            double w = wt[vec[u][i]];
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
    scanf("%d", &n);
    for(int i = 1; i <= n; i += 1)
        scanf("%d%d", &shp[i].x, &shp[i].y);
    scanf("%d", &m);
    for(int i = 1; i <= m; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        double w = getLen(u, v);
        vec[u].push_back(p);
        to[p] = v;
        wt[p ++] = w;
        vec[v].push_back(p);
        to[p] = u;
        wt[p ++] = w;
    }
    scanf("%d%d", &s, &t);
    qbbfa();
    printf("%.2lf", d[t]);
    return 0;
}