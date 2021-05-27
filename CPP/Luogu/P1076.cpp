#include <stdio.h>
using namespace std;
const int MOD = 20123;
int n, m;
int a[10007][128];
int s[10007][128];
int c[10007];
int at;
int ans;
int main(int argc, char const *argv[])
{
    // freopen("in.om", "r", stdin);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        for(int j = 0; j < m; j ++){
            scanf("%d%d", &s[i][j], &a[i][j]);
            if(s[i][j] == 1)
                c[i] ++;
        }
    }
    scanf("%d", &at);
    for(int i = 1; i <= n; i ++){
        ans += a[i][at];
        ans %= MOD;
        int walk = (a[i][at] - 1) % c[i] + 1;
        int k = at;
        k -= 1;
        if(k == -1)
            k = m - 1;
        for(int j = 0; j < walk; j ++){
            k += 1;
            if(k == m)
                k = 0;
            while(s[i][k] != 1){
                k += 1;
                if(k == m)
                    k = 0;
            }
        }
        at = k;
    }
    printf("%d", ans);
    return 0;
}