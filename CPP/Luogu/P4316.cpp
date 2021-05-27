#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct edge
{
    int to;
    int wt;
    double ps;
    edge(int v, int w, double p)
    {
        to = v;
        wt = w;
        ps = p;
    }
};
int n, m;
double sum;
vector <edge> vec[100007];
queue <edge> que;
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        vec[u].push_back(edge(v, w, 1));
    }
    que.push(edge(1, 0, 1));
    while(!que.empty())
    {
        int u = que.front().to;
        int w = que.front().wt;
        double p = que.front().ps;
        que.pop();
        if(u == n)
        {
            sum += p * w;
        }
        int len = vec[u].size();
        double _p = 1.00 / double(len);
        for(int i = 0; i < len; i++)
        {
            int v = vec[u][i].to;
            int _w = vec[u][i].wt;
            que.push(edge(v, w + _w, p * _p));
        }
    }
    printf("%.2lf", sum);
    return 0;
}
