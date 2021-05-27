#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MOD = 100003;
int n, m, p;
bool vis[1000007];
int mem[1000007];
int to[2000007];
int wt[2000007];
int d[1000007];
vector <int> vec[1000007];
queue <int> q;
inline void bf(int s){
    d[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = 0; i < (int)vec[u].size(); i ++){
            int v = to[vec[u][i]];
            int w = 1;
            if(d[v] > d[u] + w){
                d[v] = d[u] + w;
                if(!vis[v]){
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
}
inline int cnt(int u, int lim){
    int res = 0;
    if(d[u] != lim)
        return 0;
    if(u == 1)
        return 1;
    if(mem[u] != INF)
        return mem[u];
    for(int i = 0; i < (int)vec[u].size(); i ++)
        res += cnt(to[vec[u][i]], lim - 1) % MOD;
    res %= MOD;
    mem[u] = res;
    return res;
}
inline void read(int &x){
    char ch=getchar(); x=0;
    while(ch<'0') ch=getchar();
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
inline void write(int x){
    int y=10,len=1;
    while(y<=x)    {y*=10;len++;}
    while(len--){y/=10;putchar(x/y+48);x%=y;}
}
int main(int argc, char const *argv[])
{
    // init
    //freopen("in.in", "r", stdin);
    memset(d, 0x3f, sizeof(d));
    memset(mem, 0x3f, sizeof(mem));
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++){
        int u, v;
        read(u);
        read(v);
        int w = 1;
        vec[u].push_back(p);
        to[p] = v;
        wt[p ++] = w;
        vec[v].push_back(p);
        to[p] = u;
        wt[p ++] = w;
    }
    // core
    bf(1);
    for(int i = 1; i <= n; i ++){
        write(cnt(i, d[i]));
        putchar('\n');
    }
    return 0;
}