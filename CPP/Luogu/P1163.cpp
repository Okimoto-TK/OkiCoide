#include <stdio.h>
using namespace std;
int a, b, c;
bool check(double x)
{
    double y = a;
    for(int i = 1; i <= c; i++)
    {
        y = y * (1 + x / 100.0) - b;
    }
    return y <= 0;
}
int main()
{
    scanf("%d%d%d", &a, &b, &c);
    double l = 0;
    double r = 10000;
    double ans;
    while(l < r)
    {
        double mid = (l + r) / 2;
        if(check(mid))
        {
            l = mid + 0.001;
            ans = mid;
        }
        else
        {
            r = mid - 0.001;
        }
    }
    printf("%.1lf", ans);
    return 0;
}
