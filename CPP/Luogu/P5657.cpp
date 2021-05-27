#include <stdio.h>
#include <string>
using namespace std;
unsigned long long fastPow(int k){
    unsigned long long a = 2;
    unsigned long long ans = 1;
    while(k){
        if(k & 1)
            ans *= a;
        a *= a;
        k /= 2;
    }
    return ans;
}
string ra(int n, unsigned long long k){
    if(n == 1){
        if(k == 0)
            return "0";
        else
            return "1";
    }
    unsigned long long mid = fastPow(n - 1) - 1;
    unsigned long long max;
    if(n == 64)
        max = fastPow(n - 1) - 1 + fastPow(n - 1);
    else
        max = fastPow(n) - 1;
    if(k <= mid)
        return "0" + ra(n - 1, k);
    else
        return "1" + ra(n - 1, max - k);
}
unsigned long long n, k;
int main(int argc, char const *argv[])
{
    scanf("%llu%llu", &n, &k);
    printf("%s", (ra(n, k)).c_str());
    return 0;
}