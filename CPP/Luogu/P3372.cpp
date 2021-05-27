#include <stdio.h>
using namespace std;
int n, m;
int a[4000007];
long long lt[4000007];
long long s[4000007];
void plus(int k, int l, int r, long long v){
    lt[k] += v;
    s[k] += v * (r - l + 1);
} // Addition of lazy-tag
void push(int k, int l, int r){
    if(lt[k] == 0)
        return;
    int mid = (l + r) / 2;
    plus(k * 2, l, mid, lt[k]);
    plus(k * 2 + 1, mid + 1, r, lt[k]);
    lt[k] = 0;
} // Push down lazy-tag
void cons(int k, int l, int r){
    if(l == r){
        s[k] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    cons(k * 2, l, mid);
    cons(k * 2 + 1, mid + 1, r);
    s[k] = s[k * 2] + s[k * 2 + 1];
} // Construction
void proc(int k, int l, int r, int x, int y, long long v){
    if(x <= l && y >= r){
        plus(k, l, r, v);
        return;
    }
    push(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
        proc(k * 2, l, mid, x, y, v);
    if(mid < y)
        proc(k * 2 + 1, mid + 1, r, x, y, v);
    s[k] = s[k * 2] + s[k * 2 + 1];
} // Process
long long reqs(int k, int l, int r, int x, int y){
    if(l >= x && r <= y)
        return s[k];
    int mid = (l + r) / 2;
    long long req = 0;
    push(k, l, r);
    if(x <= mid)
        req += reqs(k * 2, l, mid, x, y);
    if(y > mid)
        req += reqs(k * 2 + 1, mid + 1, r, x, y);
    return req;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    cons(1, 1, n);
    for(int i = 0; i < m; i ++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int x, y;
            long long k;
            scanf("%d%d%lld", &x, &y, &k);
            proc(1, 1, n, x, y, k);
        }
        else{
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%lld\n", reqs(1, 1, n, x, y));
        }
    }
    return 0;
}