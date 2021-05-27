#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
int val[1007];
int sum[1007];
int k;
int n;
int m;
vector <int> v [1007];
queue <int> q;
int main(int argc, char const *argv[])
{
    scanf("%d%d%d", &k, &n, &m);
    for(int i = 0; i < k; i ++){
        int in;
        scanf("%d", &in);
        val[in] ++;
    }
    for(int i = 0 ; i < m; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        v[a].push_back(b);
    }
    for(int i = 1; i <= n; i ++){
        if(val[i] != 0){
            bool flg[1007] = {false};
            flg[i] = true;
            sum[i] += val[i];
            q.push(i);
            while(!q.empty()){
                int at = q.front();
                q.pop();
                for(int j = 0; j < v[at].size(); j ++){
                    if(!flg[v[at][j]]){
                        flg[v[at][j]] = true;
                        sum[v[at][j]] += val[i];
                        q.push(v[at][j]);
                    }
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i ++){
        if(sum[i] == k)
            ans ++;
    }
    printf("%d", ans);
    return 0;
}