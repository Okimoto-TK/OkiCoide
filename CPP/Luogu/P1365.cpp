#include <cstdio>
#define N 300005
int n;
char str[N];
double x1[N];
double x2[N];
int main()
{
    scanf("%d", &n);
    scanf("%s", str + 1);
    for(int i = 1; i <= n; i++)
    {
        double p = str[i] == '?' ? 0.5 : (str[i] == 'o' ? 1 : 0);
        x1[i] = p * x1[i - 1] + p;
        x2[i] = x2[i - 1] + p * (2 * x1[i - 1] + 1);
    }
    printf("%.4lf", x2[n]);
    return 0;
}
