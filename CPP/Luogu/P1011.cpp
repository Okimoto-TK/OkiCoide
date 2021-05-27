#include <stdio.h>
using namespace std;
int a, n, m, x;
int f[100007];
int u[100007];
int d[100007];
int main(int argc, char const *argv[])
{
    scanf("%d%d%d%d", &a, &n, &m, &x);
    for(int s = 0; s <= m; s ++){
        f[1] = a;
        f[2] = a;
        u[1] = a;
        u[2] = s;
        d[1] = 0;
        d[2] = s;
        for(int i = 3; i < n; i ++){
            u[i] = u[i - 1] + u[i - 2];
            d[i] = u[i - 1];
            f[i] = f[i - 1] + u[i] - d[i];
        }
        f[n] = 0;
        if(f[n - 1] == m){
            printf("%d", f[x]);
        }
    }
    return 0;
}