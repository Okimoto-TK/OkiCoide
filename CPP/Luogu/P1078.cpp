#include <stdio.h>
#include <vector>
using namespace std;
const int INF = 100000000;
int v[107][107];
int cnc[107];
int sht[107];
bool cr[107][107];
bool can = false;
int ans = -1;
int n, k, m, s, t;
void init(){
    for(int i = 0; i < 107; i ++){
        for(int j = 0; j < 107; j ++)
            v[i][j] = INF;
        sht[i] = INF;
    }
}
int getMin(int a, int b){
    return a < b ? a : b;
}
bool ref[107];
void ra(int at, int sum){
    if(can && sum >= ans)
        return;
    if(at == t){
        can = true;
        ans = sum;
        return;
    }
    if(sum > sht[at])
        return;
    sht[at] = sum;
    if(cnc[at] == cnc[t])
        return;
    for(int i = 0; i < n; i ++){
        if(v[at][i] == INF)
            continue;
        if(ref[cnc[i]])
            continue;
        bool flg = false;
        for(int j = 0; j < k; j ++)
            if(ref[j])
                if(cr[cnc[i]][j]){
                    flg = true;
                    break;
                }
        if(flg)
            continue;
        ref[cnc[i]] = true;
        ra(i, sum + v[at][i]);
        ref[cnc[i]] = false;
    }
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d%d%d%d", &n, &k, &m, &s, &t);
    s -= 1;
    t -= 1;
    for(int i = 0; i < n; i ++){
        scanf("%d", &cnc[i]);
        cnc[i] -= 1;
    }
    for(int i = 0; i < k; i ++)
        for(int j = 0; j < k; j ++){
            int x;
            scanf("%d", &x);
            if(x == 1)
                cr[i][j] = true;
            else
                cr[i][j] = false;
        }
    for(int i = 0; i < 107; i ++)
        cr[i][i] = true;
    for(int i = 0; i < m; i ++){
        int _u, _v, _d;
        scanf("%d%d%d", &_u, &_v, &_d);
        _u -= 1;
        _v -= 1;
        v[_u][_v] = getMin(v[_u][_v], _d);
        v[_v][_u] = v[_u][_v];
    }
    ref[cnc[s]] = true;
    ra(s, 0);
    printf("%d", ans);
    return 0;
}