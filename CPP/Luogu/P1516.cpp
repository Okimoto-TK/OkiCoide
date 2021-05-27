#include <stdio.h>
#include <math.h>
using namespace std;
long long x, y, m, n, l;
long long gcd(long long a, long long b){
    if(a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}
void exgcd(long long a, long long b, long long & d, long long & x0, long long & y0){
    if(b == 0){
        d = a;
        x0 = 1;
        y0 = 0;
        return;
    }
    exgcd(b, a % b, d, x0, y0);
    int t = x0;
    x0 = y0;
    y0 = t - (a / b) * y0;
}
void swap(long long & a, long long & b){
    long long t = a;
    a = b;
    b = t;
}
int main(int argc, char const *argv[])
{
    scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &l);
    long long x0;
    long long y0;
    if(n < m){
        swap(n, m);
        swap(x, y);
    }
    long long c = x - y;
    long long a = n - m;
    long long b = l;
    long long d;
    long long g = gcd(a, b);
    if(c % g != 0 || a == 0){
        printf("Impossible");
        return 0;
    }
    exgcd(a, b, d, x0, y0);
    a /= g;
    b /= g;
    c /= g;
    x0 *= c;
    y0 *= c;
    printf("%lld", ((x0 % b + b) % b));
    return 0;
}