#include <cstdio>
#include <cmath>
#define N (int)1e5 + 5
int m, n;
double ans;
int main()
{
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= m; i++) { ans += i * (pow(double(i) / double(m), n) - pow(double(i - 1) / double(m), n)); }
    printf("%.6lf", ans);
    return 0;
}
