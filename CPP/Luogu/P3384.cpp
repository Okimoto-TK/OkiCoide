#include <stdio.h>
#include <vector>
using namespace std;
int n, m, r, p;
int num[100007];
int seg[100007];
int dep[100007];
int top[100007];
int son[100007];
int ref[100007];
int siz[100007];
int sup[100007];
long long s[1000007];
long long lz[1000007];
vector <int> vec[100007];
void dfsOne(int at, int super){
    siz[at] = 1;
    dep[at] = dep[super] + 1;
    sup[at] = super;
    for(int i = 0; i < vec[at].size(); i ++){
        int to = vec[at][i];
        if(to == super)
            continue;
        dfsOne(to, at);
        siz[at] += siz[to];
        if(siz[to] > siz[son[at]])
            son[at] = to;
    }
}
void dfsTwo(int at, int super){
    if(son[at]){
        seg[son[at]] = ++ seg[0];
        ref[seg[0]] = son[at];
        top[son[at]] = top[at];
        dfsTwo(son[at], at);
    }
    for(int i = 0; i < vec[at].size(); i ++){
        int to = vec[at][i];
        if(to == son[at] || to == super)
            continue;
        seg[to] = ++ seg[0];
        ref[seg[0]] = to;
        top[to] = to;
        dfsTwo(to, at);
    }
}
void constr(int k, int l, int r){
    if(l == r){
        s[k] = num[ref[l]] % p;
        return;
    }
    int mid = (l + r) >> 1;
    constr(k << 1, l, mid);
    constr(k << 1 | 1, mid + 1, r);
    s[k] = (s[k << 1] % p + s[k << 1 | 1] % p) % p;
}
void incrse(int k, int l, int r, int v){
    s[k] = (s[k] % p + (v * (r - l + 1)) % p) % p;
    lz[k] = (lz[k] % p + v % p) % p;
}
void pshDwn(int k, int l, int r){
    if(lz[k] == 0)
        return;
    int mid = (l + r) >> 1;
    incrse(k << 1, l, mid, lz[k]);
    incrse(k << 1 | 1, mid + 1, r, lz[k]);
    lz[k] = 0;
}
void change(int k, int l, int r, int x, int y, int v){
    if(l >= x && r <= y){
        incrse(k, l, r, v);
        return;
    }
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
        change(k << 1, l, mid, x, y, v);
    if(y > mid)
        change(k << 1 | 1, mid + 1, r, x, y, v);
    s[k] = (s[k << 1] % p + s[k << 1 | 1] % p) % p;
}
long long requir(int k, int l, int r, int x, int y){
    if(l >= x && r <= y)
        return s[k];
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid)
        res = (res % p + requir(k << 1, l, mid, x, y) % p) % p;
    if(y > mid)
        res = (res % p + requir(k << 1 | 1, mid + 1, r, x, y) % p) % p;
    return res;
}
void swap(int & x, int & y){
    int t = x;
    x = y;
    y = t;
}
void proTre(int x, int y, int z){
    int fx = top[x];
    int fy = top[y];
    while(fx != fy){
        if(dep[fx] < dep[fy]){
            swap(fx, fy);
            swap(x, y);
        }
        change(1, 1, seg[0], seg[fx], seg[x], z);
        x = sup[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
        swap(x, y);
    change(1, 1, seg[0], seg[x], seg[y], z);
}
long long askTre(int x, int y){
    int fx = top[x];
    int fy = top[y];
    long long res = 0;
    while(fx != fy){
        if(dep[fx] < dep[fy]){
            swap(fx, fy);
            swap(x, y);
        }
        res = requir(1, 1, seg[0], seg[fx], seg[x]) % p + res % p;
        res %= p;
        x = sup[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
        swap(x, y);
    return (res % p + requir(1, 1, seg[0], seg[x], seg[y]) % p) % p;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d%d%d", &n, &m, &r, &p);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &num[i]);
    for(int i = 1; i < n; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    dfsOne(r, 0);
    seg[r] = ++ seg[0];
    ref[seg[0]] = r;
    top[r] = r;
    dfsTwo(r, 0);
    constr(1, 1, seg[0]);
    for(int i = 0; i < m; i ++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            proTre(x, y, z);
        }
        else if(t == 2){
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%lld\n", askTre(x, y));
        }
        else if(t == 3){
            int x, z;
            scanf("%d%d", &x, &z);
            change(1, 1, seg[0], seg[x], seg[x] + siz[x] - 1, z);
        }
        else{
            int x;
            scanf("%d", &x);
            printf("%lld\n", requir(1, 1, seg[0], seg[x], seg[x] + siz[x] - 1) % p);
        }
    }
    return 0;
}