#include <stdio.h>
using namespace std;
int n, m, p;
long long lazyTag[1000007];
long long lazyTagM[1000007];
long long segmentTree[1000007];
int original[1000007];
void init(){
    for(int i = 0; i < 1000007; i ++)
        lazyTagM[i] = 1;
}
void increase(int k, int l, int r, long long v){
    lazyTag[k] += v % p;
    lazyTag[k] %= p;
    segmentTree[k] += v * (r - l + 1) % p;
    segmentTree[k] %= p;
}
void multiply(int k, int l, int r, long long f){
    lazyTagM[k] *= f % p;
    lazyTagM[k] %= p;
    lazyTag[k] *= f % p;
    lazyTag[k] %= p;
    segmentTree[k] *= f % p;
    segmentTree[k] %= p;
}
void pushDown(int k, int l, int r){
    if(lazyTag[k] == 0 && lazyTagM[k] == 1)
        return;
    int middle = (l + r) / 2;
    multiply(k * 2, l, middle, lazyTagM[k]);
    increase(k * 2, l, middle, lazyTag[k]);
    multiply(k * 2 + 1, middle + 1, r, lazyTagM[k]);
    increase((k * 2) + 1, middle + 1, r, lazyTag[k]);
    lazyTag[k] = 0;
    lazyTagM[k] = 1;
}
void construct(int k, int l, int r){
    if(l == r){
        segmentTree[k] = original[l] % p;
        return;
    }
    int middle = (l + r) / 2;
    construct(k * 2, l, middle);
    construct((k * 2) + 1, middle + 1, r);
    segmentTree[k] = (segmentTree[k * 2] + segmentTree[(k * 2) + 1]) % p;
}
void addition(int k, int l, int r, int x, int y, long long v){
    if(l >= x && r <= y){
        increase(k, l, r, v);
        return;
    }
    pushDown(k, l, r);
    int middle = (l + r) / 2;
    if(x <= middle)
        addition(k * 2, l, middle, x, y, v);
    if(y > middle)
        addition((k * 2) + 1, middle + 1, r, x, y, v);
    segmentTree[k] = (segmentTree[k * 2] + segmentTree[(k * 2) + 1]) % p;
}
void multiplication(int k, int l, int r, int x, int y, long long f){
    if(x <= l && r <= y){
        multiply(k, l, r, f);
        return;
    }
    pushDown(k, l, r);
    int middle = (l + r) / 2;
    if(x <= middle)
        multiplication(k * 2, l, middle, x, y, f);
    if(y > middle)
        multiplication(k * 2 + 1, middle + 1, r, x, y, f);
    segmentTree[k] = (segmentTree[k * 2] + segmentTree[(k * 2) + 1]) % p;
}
long long request(int k, int l, int r, int x, int y){
    if(l >= x && r <= y)
        return segmentTree[k] % p;
    pushDown(k, l, r);
    long long response = 0;
    int middle = (l + r) / 2;
    if(x <= middle)
        response = (response % p + request(k * 2, l, middle, x, y) % p) % p; 
    if(y > middle)
        response = (response % p + request((k * 2) + 1, middle + 1, r, x, y) % p) % p;
    return response % p;
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d%d", &n, &p);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &original[i]);
    construct(1, 1, n);
    scanf("%d", &m);
    for(int i = 1; i <= m; i ++){
        int t;
        scanf("%d", &t);
        if(t == 2){
            int x, y;
            long long k;
            scanf("%d%d%lld", &x, &y, &k);
            addition(1, 1, n, x, y, k);
            //flag
        }
        else if(t == 1){
            int x, y;
            long long k;
            scanf("%d%d%lld", &x, &y, &k);
            multiplication(1, 1, n, x, y, k);
        }
        else{
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%lld\n", request(1, 1, n, x, y));
        }
    }
    return 0;
}