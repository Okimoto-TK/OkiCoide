#include <stdio.h>
using namespace std;
int n, f;
long long s[200007];
long long c[200007];
long long d[200007];
int lowbit(int x){
    return x & (-x);
}
void upd(int x, long long k){
    for(; x <= n; x += lowbit(x))
        c[x] += k;
}
void _upd(int x, long long k){
    for(; x <= n; x += lowbit(x))
        d[x] += k;
}
long long sum(int x){
    long long r = 0;
    for(; x; x -= lowbit(x))
        r += c[x];
    return r;
}
long long _sum(int x){
    long long r = 0;
    for(; x; x -= lowbit(x))
        r += d[x];
    return r;
}
int main(){
    scanf("%d%d", &n, &f);
    for(int i = 1; i <= n; i ++){
        long long v;
        scanf("%lld", &v);
        s[i] = s[i - 1] + v;
    }
    for(int i = 0; i < f; i ++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int l, r;
            long long k;
            scanf("%d%d%lld", &l, &r, &k);
            upd(l, k);
            _upd(l, l * k);
            upd(r + 1, -k);
            _upd(r + 1, (r + 1) * (-k));
        }
        else if(t == 2){
            long long k;
            scanf("%lld", &k);
            upd(1, k);
            _upd(1, k);
            upd(2, -k);
            _upd(2, -2 * k);
        }
        else if(t == 3){
            long long k;
            scanf("%lld", &k);
            upd(1, -k);
            _upd(1, -k);
            upd(2, k);
            _upd(2, 2 * k);
        }
        else if(t == 4){
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", (s[r] + (r + 1) * sum(r) - _sum(r)) - (s[l - 1] + l * sum(l - 1) - _sum(l - 1)));
        }
        else
            printf("%lld\n", s[1] + sum(1));
    }
    return 0;
}