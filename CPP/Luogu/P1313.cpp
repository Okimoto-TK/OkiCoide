#include <stdio.h>
using namespace std;
const int p = 10007;
int f[1007][1007];
int com(int n, int m)
{
    if(m == 0){ return 1; }
    if(n == m){ return 1; }
    if(f[n][m] != 0){ return f[n][m]; }
    f[n][m] = (com(n - 1, m - 1) % p + com(n - 1, m) % p) % p;
    return f[n][m];
}
int mod(int x, int k)
{
    x %= p;
    int r = 1;
    while(k)
    {
        if(k & 1)
        {
            r *= x;
            r %= p;
        }
        k /= 2;
        x *= x;
        x %= p;
    }
    return r;
}
int a, b, k, n, m;
int main()
{
    scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
    printf("%d", mod(a, n) % p * mod(b, m) % p * com(k, n) % p);
    return 0;
}
