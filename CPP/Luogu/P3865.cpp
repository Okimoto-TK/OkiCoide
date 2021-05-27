#include <stdio.h>
using namespace std;
int getMax(int a, int b){
    return a > b ? a : b;
}
int n, m;
int a[1000007];
int f[1000007][32];
int lg[1000007];
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
    }
    lg[0] = -1;
    for(int i = 1; i <= n; i ++){
        f[i][0] = a[i];
        lg[i] = lg[i >> 1] + 1;
    }
    for(int j = 1; j <= 30; j ++){
        for(int i = 1; i + (1 << j) - 1 <= n; i ++){
            f[i][j] = getMax(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
    for(int i = 0; i < m; i ++){
        int l, r;
        scanf("%d%d", &l, &r);
        int s = lg[r - l + 1];
        printf("%d\n", getMax(f[l][s], f[r - (1 << s) + 1][s]));
    }
    return 0;
}
