#include <stdio.h>
using namespace std;
const int mod = 1e8;
int gcd(int a, int b)
{
    if(b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int x = gcd(n, m);
    if(x == 0 || x == 1)
    {
        printf("1");
        return 0;
    }
    int ll = 1;
    int l = 1;
    int i = 2;
    if(x > 500000000)
    {
        l = 390626;
        ll = 39453125;
        i = 500000001;
    }
    for(; i < x; i++)
    {
        int t = l + ll;
        ll = l;
        l = t % mod;
    }
    printf("%d", l);
    return 0;
}
