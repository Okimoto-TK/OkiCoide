#include <stdio.h>
#include <math.h>
using namespace std;
long long gcd(long long a, long long b){
    if(a % b == 0)
        return b;
    return gcd(b, a % b);
}
void exgcd(long long a, long long b, long long & d, long long & x, long long & y){
    if(b == 0){
        d = a;
        x = 1;
        y = 0;
    }
    else{
        exgcd(b, a % b, d, x, y);
        long long t = x;
        x = y;
        y = t - (a / b) * y;
    }
}
long long t;
int main(int argc, char const *argv[])
{
    //freopen("out.out", "w", stdout);
    scanf("%lld", &t);
    for(int i = 0; i < t; i ++){
        long long a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        long long d = gcd(a, b);
        if(c % d != 0){
            printf("-1\n");
            continue;
        }
        long long _a = a / d;
        long long _b = b / d;
        long long _c = c / d;
        long long x0;
        long long y0;
        exgcd(_a, _b, d, x0, y0);
        x0 *= _c;
        y0 *= _c;
        long long kx = _b; // IIDD
        long long ky = -1 * _a; // IDDI
        long long bx = x0;
        long long by = y0;
        double xlx = -1 * (double(bx) / double(kx));
        double xly = -1 * (double(by) / double(ky));
        long long ax = (int)floor(xlx + 1.0);
        long long ay = (int)ceil(xly - 1.0);
        if(ay - ax + 1 <= 0){
            long long minx = kx * ax + bx;
            long long miny = ky * ay + by;
            printf("%lld %lld\n", minx, miny);
        }
        else{
            long long num = ay - ax + 1;
            long long minx = kx * ax + bx;
            long long miny = ky * ay + by;
            long long maxx = kx * ay + bx;
            long long maxy = ky * ax + by;
            printf("%lld %lld %lld %lld %lld\n", num, minx, miny, maxx, maxy);
        }
    }
    return 0;
}