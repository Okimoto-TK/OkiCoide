#include <stdio.h>
#include <vector>
using namespace std;
int n, m;
int num[100007];
int seg[100007];
int ref[100007];
int dep[100007];
int top[100007];
int sup[100007];
int son[100007];
int size[100007];
long long s[400007];
long long lz[400007];
vector <int> v[100007];
void dfsOne(int at, int super){
    dep[at] = dep[super] + 1;
    sup[at] = super;
    size[at] = 1;
    for(int i = 0; i < v[at].size(); i ++){
        int to = v[at][i];
        if(to == super)
            continue;
        dfsOne(to, at);
        size[at] += size[to];
        if(size[to] > size[son[at]])
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
    for(int i = 0; i < v[at].size(); i ++){
        int to = v[at][i];
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
        s[k] = num[ref[l]];
        return;
    }
    int mid = (l + r) >> 1;
    constr(k << 1, l, mid);
    constr(k << 1 | 1, mid + 1, r);
    s[k] = s[k << 1] + s[k << 1 | 1];
}
void add(int k, int l, int r, long long _v){
    s[k] += _v * (r - l + 1);
    lz[k] += _v;
}
void pshDwn(int k, int l, int r){
    if(lz[k] == 0)
        return;
    int mid = (l + r) >> 1;
    add(k << 1, l, mid, lz[k]);
    add(k << 1 | 1, mid + 1, r, lz[k]);
    lz[k] = 0;
}
void change(int k, int l, int r, int x, int y, long long _v){
    if(l >= x && r <= y){
        add(k, l, r, _v);
        return;
    }
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
        change(k << 1, l, mid, x, y, _v);
    if(y > mid)
        change(k << 1 | 1, mid + 1, r, x, y, _v);
    s[k] = s[k << 1] + s[k << 1 | 1];
}
long long req(int k, int l, int r, int x, int y){
    if(l >= x && r <= y){
        return s[k];
    }
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid)
        res += req(k << 1, l, mid, x, y);
    if(y > mid)
        res += req(k << 1 | 1, mid + 1, r, x, y);
    return res;
}
void swap(int & x, int & y){
    int t = x;
    x = y;
    y = t;
}
long long ask(int x, int y){
    int fx = top[x];
    int fy = top[y];
    long long res = 0;
    while(fx != fy){
        if(dep[fx] < dep[fy]){
            swap(fx, fy);
            swap(x, y);
        }
        res += req(1, 1, seg[0], seg[fx], seg[x]);
        x = sup[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
        swap(x, y);
    return res + req(1, 1, seg[0], seg[x], seg[y]);
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &num[i]);
    for(int i = 1; i < n; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfsOne(1, 0);
    seg[1] = ++ seg[0];
    ref[seg[0]] = 1;
    top[1] = 1;
    dfsTwo(1, 0);
    constr(1, 1, seg[0]);
    for(int i = 0; i < m; i ++){
        int t;
        scanf("%d", &t);
        if(t == 1){
            int x, a;
            scanf("%d%d", &x, &a);
            change(1, 1, seg[0], seg[x], seg[x], a);
        }
        else if(t == 2){
            int x, a;
            scanf("%d%d", &x, &a);
            change(1, 1, seg[0], seg[x], seg[x] + size[x] - 1, a);
        }
        else{
            int x;
            scanf("%d", &x);
            printf("%lld\n", ask(1, x));
        }
    }
    return 0;
}