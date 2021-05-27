#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
double getT(double d)
{
    return sqrt(d / 5.0);
}
double h, s, v, l, k;
int n, ans;
int main()
{
    scanf("%lf%lf%lf%lf%lf%d", &h, &s, &v, &l, &k, &n);
    double st = getT(h - k);
    double bt = getT(h);
    //printf("%lf %lf\n", st, bt);
    for(double i = n - 1; i >= 0; i--)
    {
        double at = (s - i) / v;
        double dt = (s + l - i) / v;
        //printf("%lf %lf\n", at, dt);
        if(max(st, at) - min(bt, dt) <= (0.0001 / v))
        {
            ans += 1;
        }
    }
    printf("%d", ans);
    return 0;
}
