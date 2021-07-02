#include <cstdio>
int a[10];
int sum;
double e = 1.0;
int main()
{
    for(int i = 1; i <= 7; i++)
    {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    if(sum <= 6)
    {
        printf("0.000");
        return 0;
    }
    for(int i = 1; i <= 7; i++)
    {
        e *= double(a[i]) / (sum - i + 1);
        e *= i;
    }
    e *= (sum - 6);
    printf("%.3lf", e);
    return 0;
}

