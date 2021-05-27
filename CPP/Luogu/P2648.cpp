#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
int d, p, c, f;
int wt[1007];
int to[1007];
int res[1007];
int cnt[1007];
bool bn[1007];
int ans = 100000000;
int mn;
vector <int> vec[1007];
int ptr;
queue <int> q;
int getmn(int a, int b){
    return a < b ? a : b;
}
bool qbbfa(int s){
    memset(res, 0x3f, sizeof(res));
    memset(bn, 0, sizeof(bn));
    memset(cnt, 0, sizeof(cnt));
    res[s] = -d;
    bn[s] = true;
    mn = res[s];
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cnt[u] ++;
        if(cnt[u] >= c)
            return false;
        bn[u] = false;
        for(int i = 0; i < vec[u].size(); i ++){
            int v = to[vec[u][i]];
            int w = wt[vec[u][i]];
            if(res[v] > res[u] + w){
                res[v] = res[u] + w;
                mn = getmn(mn, res[v]);
                if(!bn[v]){
                    q.push(v);
                    bn[v] = true;
                }
            }
        }
    }
    return true;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d%d%d", &d, &p, &c, &f);
    for(int i = 0; i < p; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(ptr);
        to[ptr] = v;
        wt[ptr ++] = -1 * d;
    }
    for(int i = 0; i < f; i ++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        vec[u].push_back(ptr);
        to[ptr] = v;
        wt[ptr ++] = -(d - w);
    }
    for(int i = 1; i <= c; i ++){
        if(qbbfa(i)){
            ans = getmn(ans, mn);
        }
        else{
            printf("orz");
            return 0;
        }
    }
    printf("%d", -ans);
    return 0;
}