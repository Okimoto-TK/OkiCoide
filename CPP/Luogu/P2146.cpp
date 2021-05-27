#include <stdio.h>
#include <vector>
using namespace std;
int n, q;
int siz[100007];
int dep[100007];
int son[100007];
int sup[100007];
int top[100007];
int seg[100007];
int ref[100007];
int lz[400007];
int s[2][400007];
bool iLz[400007];
vector <int> vec[100007];
void dfsOne(int at, int super){
    siz[at] = 1;
    dep[at] = dep[super] + 1;
    sup[at] = super;
    for(int i = 0; i < vec[at].size(); i ++){
        int to = vec[at][i];
        dfsOne(to, at);
        siz[at] += siz[to];
        if(siz[to] > siz[son[at]])
            son[at] = to;
    }
}
void dfsTwo(int at){
    if(son[at]){
        seg[son[at]] = ++ seg[0];
        ref[seg[0]] = son[at];
        top[son[at]] = top[at];
        dfsTwo(son[at]);
    }
    for(int i = 0; i < vec[at].size(); i ++){
        int to = vec[at][i];
        if(to == son[at])
            continue;
        seg[to] = ++ seg[0];
        ref[seg[0]] = to;
        top[to] = to;
        dfsTwo(to);
    }
}
void constr(int k, int l, int r){
    if(l == r){
        s[1][k] = 0;
        s[0][k] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    constr(k << 1, l, mid);
    constr(k << 1 | 1, mid + 1, r);
    s[0][k] = s[0][k << 1] + s[0][k << 1 | 1];
    s[1][k] = s[1][k << 1] + s[1][k << 1 | 1];
}
void change(int k, int l, int r, int v){
    if(v == 1){
        s[1][k] = r - l + 1;
        s[0][k] = 0;
        lz[k] = 1;
    }
    else{
        s[0][k] = r - l + 1;
        s[1][k] = 0;
        lz[k] = 0;
    }
    iLz[k] = true;
}
void pshDwn(int k, int l, int r){
    if(!iLz[k])
        return;
    int mid = (l + r) >> 1;
    change(k << 1, l, mid, lz[k]);
    change(k << 1 | 1, mid + 1, r, lz[k]);
    iLz[k] = false;
}
int requir(int k, int l, int r, int x, int y, int v){
    if(l >= x && r <= y)
        return s[v][k];
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid)
        res += requir(k << 1, l, mid, x, y, v);
    if(y > mid)
        res += requir(k << 1 | 1, mid + 1, r, x, y, v);
    return res;
}
void modify(int k, int l, int r, int x, int y, int v){
    if(l >= x && r <= y){
        change(k, l, r, v);
        return;
    }
    pshDwn(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
        modify(k << 1, l, mid, x, y, v);
    if(y > mid)
        modify(k << 1 | 1, mid + 1, r, x, y, v);
    s[0][k] = s[0][k << 1] + s[0][k << 1 | 1];
    s[1][k] = s[1][k << 1] + s[1][k << 1 | 1];
}
void swap(int & x, int & y){
    int t = x;
    x = y;
    y = t;
}
int askTre(int x, int y, int v){
    int fx = top[x];
    int fy = top[y];
    int res = 0;
    while(fx != fy){
        if(dep[fx] < dep[fy]){
            swap(fx, fy);
            swap(x, y);
        }
        res += requir(1, 1, seg[0], seg[fx], seg[x], v == 1 ? 0 : 1);
        modify(1, 1, seg[0], seg[fx], seg[x], v);
        x = sup[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
        swap(x, y);
    res += requir(1, 1, seg[0], seg[x], seg[y], v == 1 ? 0 : 1);
    modify(1, 1, seg[0], seg[x], seg[y], v);
    return res;
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 1; i < n; i ++){
        int a;
        scanf("%d", &a);
        vec[a + 1].push_back(i + 1);
    }
    dfsOne(1, 0);
    seg[1] = ++ seg[0];
    ref[seg[0]] = 1;
    top[1] = 1;
    dfsTwo(1);
    constr(1, 1, seg[0]);
    scanf("%d", &q);
    for(int i = 0; i < q; i ++){
        char c[16];
        int x;
        scanf("%s", c);
        scanf("%d", &x);
        x += 1;
        if(c[0] == 'i')
            printf("%d\n", askTre(1, x, 1));
        else{
            printf("%d\n", requir(1, 1, seg[0], seg[x], seg[x] + siz[x] - 1, 1));
            modify(1, 1, seg[0], seg[x], seg[x] + siz[x] - 1, 0);
        }
    }
    return 0;
}