#include <stdio.h>
using namespace std;
int n, p;
long long tag[1000007];
long long a[1000007];
const long long INF = 100000000000000L;
struct bigInt
{
    long long a, b;
    void print(){
        if(b < 0){
            printf("%lld", -b % p * -1);
        }
        else{
            if(a != 0){
                printf("%lld", (long long)((a % p) * (INF % p) + b) % p);
            }
            else{
                printf("%lld", b % p);
            }
        }
    }
    void tide(){
        if(b <= 0){
            while(a > 0 && b <= 0){
                b += INF;
                a -= 1;
            }
        }
        if(b > INF){
            a += b / INF;
            b %= INF;
        }
    }
} sc[1000007];
bigInt add(bigInt a, long long b){
    bigInt r;
    r.a = a.a;
    r.b = a.b + b;
    r.tide();
    return r;
}
long long getMax(long long a, long long b){
    return a > b ? a : b;
}
long long getAbs(long long a){
    return a > 0 ? a : -a;
}
bigInt getMax(bigInt a, bigInt b){
    if(a.a == b.a){
        if(a.b > b.b)
            return a;
        else
            return b;
    }
    if(a.a < b.a)
        return b;
    else
        return a;
}
void initTag(){
    long long max = -9223372036854775808L;
    long long sum = 0;
    for(int i = 0; i < n; i ++){
        sum += a[i];
        max = getMax(max, sum);
        if(sum < 0){
            sum = 0;
        }
        tag[i] = max;
    }
}
void initSc(){
    bigInt max;
    max.a = -99999999999999999L;
    max.b = -99999999999999999L;
    sc[0].b = tag[0];
    sc[0].a = 0;
    sc[0].tide();
    max = getMax(max, add(sc[0], tag[0]));
    for(long long i = 1; i < n; i ++){
        sc[i] = max;
        sc[i].tide();
        max = getMax(add(sc[i], tag[i]), max);
    }
}
int main(int argc, char const *argv[])
{
    freopen("in.om", "r", stdin);
    scanf("%lld%lld", &n, &p);
    for(int i = 0; i < n; i ++)
        scanf("%lld", &a[i]);
    initTag();
    initSc();
    bigInt max;
    max.a = -99999999999999999L;
    max.b = -99999999999999999L;
    for(int i = 0; i < n; i ++)
        max = getMax(max, sc[i]);
    max.print();
    return 0;
}