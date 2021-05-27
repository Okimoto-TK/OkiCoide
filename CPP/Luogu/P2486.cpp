#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
struct node
{
    int l;
    int r;
    int v;
    node(){
        l = 0;
        r = 0;
        v = 0;
    }
};
int n, m;
int son[100007];
int seg[100007];
int top[100007];
int ref[100007];
int siz[100007];
int sup[100007];
int dep[100007];
int ori[100007];
int lz[400007];
node s[400007];
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
        top[son[at]] = top[at];
        ref[seg[0]] = son[at];
        dfsTwo(son[at], at);
    }
    for(int i = 0; i < vec[at].size(); i ++){
        int to = vec[at][i];
        if(to == super || to == son[at])
            continue;
        seg[to] = ++ seg[0];
        ref[seg[0]] = to;
        top[to] = to;
        dfsTwo(to, at);
    }
}
void constr(int k, int l, int r){
    if(l == r){
        s[k].l = ori[ref[l]];
        s[k].r = ori[ref[l]];
        s[k].v = 1;
        return;
    }
    int mid = (l + r) >> 1;
    constr(k << 1, l, mid);
    constr(k << 1 | 1, mid + 1, r);
    s[k].l = s[k << 1].l;
    s[k].r = s[k << 1 | 1].r;
    if(s[k << 1].r == s[k << 1 | 1].l)
        s[k].v = s[k << 1].v + s[k << 1 | 1].v - 1;
    else
        s[k].v = s[k << 1].v + s[k << 1 | 1].v;
}
void paintC(int k, int l, int r, int v){
    s[k].v = 1;
    s[k].l = v;
    s[k].r = v;
    lz[k] = v;
}
void pshDwn(int k, int l, int r){
    if(lz[k] == 0)
        return;
    int mid = (l + r) >> 1;
    paintC(k << 1, l, mid, lz[k]);
    paintC(k << 1 | 1, mid + 1, r, lz[k]);
    lz[k] = 0;
}
void colour(int k, int l, int r, int x, int y, int v){
    if(l >= x && r <= y){
        paintC(k, l, r, v);
        return;
    }
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
        colour(k << 1, l, mid, x, y, v);
    if(y > mid)
        colour(k << 1 | 1, mid + 1, r, x, y, v);
    s[k].l = s[k << 1].l;
    s[k].r = s[k << 1 | 1].r;
    if(s[k << 1].r == s[k << 1 | 1].l)
        s[k].v = s[k << 1].v + s[k << 1 | 1].v - 1;
    else
        s[k].v = s[k << 1].v + s[k << 1 | 1].v;
}
node requir(int k, int l, int r, int x, int y){
    if(l >= x && r <= y)
        return s[k];
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    node res;
    if(x <= mid && !(y > mid)){
        node lr = requir(k << 1, l, mid, x, y);
        res.v = lr.v;
        res.l = lr.l;
        res.r = lr.r;
    }
    else if(y > mid && !(x <= mid)){
        node rr = requir(k << 1 | 1, mid + 1, r, x, y);
        res.v = rr.v;
        res.l = rr.l;
        res.r = rr.r;
    }
    else{
        node lr = requir(k << 1, l, mid, x, y);
        node rr = requir(k << 1 | 1, mid + 1, r, x, y);
        if(lr.r == rr.l)
            res.v = lr.v + rr.v - 1;
        else
            res.v = lr.v + rr.v;
        res.l = lr.l;
        res.r = rr.r;
    }
    return res;
}
void swap(int & a, int & b){
    int t = a;
    a = b;
    b = t;
}
void paintT(int a, int b, int c){
    int fa = top[a];
    int fb = top[b];
    while(fa != fb){
        if(dep[fa] < dep[fb]){
            swap(fa, fb);
            swap(a, b);
        }
        colour(1, 1, seg[0], seg[fa], seg[a], c);
        a = sup[fa];
        fa = top[a];
    }
    if(dep[a] > dep[b])
        swap(a, b);
    colour(1, 1, seg[0], seg[a], seg[b], c);
}
void revers(int & x){
    x ^= 1;
}
int countT(int a, int b){
    int f = 0;
    bool ini[2] = {false};
    node ans[2];
    int fa = top[a];
    int fb = top[b];
    while(fa != fb){
        if(dep[fa] < dep[fb]){
            swap(fa, fb);
            swap(a, b);
            revers(f);
        }
        if(!ini[f]){
            ans[f] = requir(1, 1, seg[0], seg[fa], seg[a]);
            ini[f] = true;
        }
        else{
            node r = requir(1, 1, seg[0], seg[fa], seg[a]);
            ans[f].v += r.v;
            if(ans[f].l == r.r)
                ans[f].v -= 1;
            ans[f].l = r.l;
        }
        a = sup[fa];
        fa = top[a];
    }
    if(dep[a] > dep[b]){
        swap(a, b);
        revers(f);
    }
    node r = requir(1, 1, seg[0], seg[a], seg[b]);
    r.v += ans[0].v;
    r.v += ans[1].v;
    if(ans[f].l == r.l)
        r.v -= 1;
    revers(f);
    if(ans[f].l == r.r)
        r.v -= 1;
    return r.v;
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &ori[i]);
    for(int i = 1; i < n; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfsOne(1, 0);
    seg[1] = ++ seg[0];
    ref[seg[0]] = 1;
    top[1] = 1;
    dfsTwo(1, 0);
    constr(1, 1, seg[0]);
    for(int i = 0; i < m; i ++){
        char op[2];
        scanf("%s", op);
        if(op[0] == 'C'){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            paintT(a, b, c);
        }
        else{
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d\n", countT(a, b));
        }
    }
    return 0;
}