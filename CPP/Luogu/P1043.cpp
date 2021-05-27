#include <stdio.h>
using namespace std;
int n, m;
int sum[107];
int a[107];
long long f[107][107][107];
long long _f[107][107][107];
long long INF = 100000000000L;
int getMod(int a){
    return ((a % 10 + 10) % 10);
}
long long getMax(long long a, long long b){
    return a > b ? a : b;
}
long long getMin(long long a, long long b){
    return a < b ? a : b;
}
void init(){
    for(int i = 0; i < 10; i ++)
        for(int j = 0; j < 107; j ++)
            for(int k = 0; k < 107; k ++)
                _f[i][j][k] = INF;
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i ++){
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }
    for(int i = 0; i < 2 * n; i ++){
        f[1][i][i] = getMod(a[i]);
        _f[1][i][i] = getMod(a[i]);
        sum[i + 1] = a[i] + sum[i];
    }
    for(int l = 2; l <= n; l ++){
        for(int i = 0; i < n; i ++){
            int j = i + l - 1;
            f[1][i][j] = getMod(sum[j + 1] - sum[i]);
            _f[1][i][j] = getMod(sum[j + 1] - sum[i]);
            for(int g = 2; g <= l; g ++){
                for(int h = 1; h < g; h ++){
                    int _h = g - h;
                    for(int k = i; k < j; k ++){
                        if(k - i + 1 < h || j - k < _h)
                            continue;
                        _f[g][i][j] = getMin(_f[g][i][j], _f[h][i][k] * _f[_h][k + 1][j]);
                        f[g][i][j] = getMax(f[g][i][j], f[h][i][k] * f[_h][k + 1][j]);
                    }
                }
            }
        }
    }
    long long ans = 0;
    long long _ans = INF;
    for(int i = 0; i < n; i ++){
        ans = getMax(ans, f[m][i][i + n - 1]);
        _ans = getMin(_ans, _f[m][i][i + n - 1]);
    }
    printf("%lld\n%lld", _ans, ans);
    return 0;
}