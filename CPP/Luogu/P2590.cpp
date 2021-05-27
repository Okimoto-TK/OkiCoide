#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
int n, q;
vector <int> v[100007]; // 领接表
int super[100007]; // 点的父亲
int size[100007]; // 点的子节点数量
int depth[100007]; // 点深度
int w[100007]; // 点权值
int s[1000007]; // 节点编号 -> 线段树编号
int rps[1000007]; // 线段树编号 -> 节点编号
int top[100007]; // 重链头
int t[1000007]; // 线段树的Sum数组
int m[1000007]; // 线段树的Max数组
int son[100007]; // 儿砸
bool us[100007]; // DFS1的表
bool use[100007]; // DFS2的表
int AnsS; // Sum
int AnsM; // Max
void swap(int & a, int & b){
    int tmp = a;
    a = b;
    b = tmp;
}
void dfsOne(int u, int s){
    us[u] = true;
    size[u] = 1;
    super[u] = s;
    depth[u] = depth[s] + 1;
    for(int i = 0; i < (int)v[u].size(); i ++){
        if(us[v[u][i]])
            continue;
        dfsOne(v[u][i], u);
        size[u] += size[v[u][i]];
        if(size[v[u][i]] > size[son[u]])
            son[u] = v[u][i];
    }
}
void dfsTwo(int u){
    use[u] = true;
    if(son[u]){
        s[son[u]] = ++ s[0];
        rps[s[0]] = son[u];
        top[son[u]] = top[u];
        dfsTwo(son[u]);
    }
    for(int i = 0; i < (int)v[u].size(); i ++){
        if(use[v[u][i]])
            continue;
        s[v[u][i]] = ++ s[0];
        rps[s[0]] = v[u][i];
        top[v[u][i]] = v[u][i];
        dfsTwo(v[u][i]);
    }
}
int getMax(int a, int b){
    return a > b ? a : b;
}
void con(int k, int l, int r){
    if(l == r){
        m[k] = w[rps[l]];
        t[k] = w[rps[l]];
        return;
    }
    int mid = (l + r) >> 1;
    con(k << 1, l, mid);
    con(k << 1 | 1, mid + 1, r);
    t[k] = t[k << 1] + t[k << 1 | 1];
    m[k] = getMax(m[k << 1], m[k << 1 | 1]);
}
void pro(int k, int l, int r, int x, int _v){
    if(l == x && r == x){
        t[k] = _v;
        m[k] = _v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
        pro(k << 1, l, mid, x, _v);
    if(x > mid)
        pro(k << 1 | 1, mid + 1, r, x, _v);
    t[k] = t[k << 1] + t[k << 1 | 1];
    m[k] = getMax(m[k << 1], m[k << 1 | 1]);
}
void req(int k, int l, int r, int x, int y){
    if(l >= x && r <= y){
        AnsS += t[k];
        AnsM = getMax(AnsM, m[k]);
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
        req(k << 1, l, mid, x, y);
    if(y > mid)
        req(k << 1 | 1, mid + 1, r, x, y);
}
void ask(int x, int y){
    int fx = top[x];
    int fy = top[y];
    while(fx != fy){
        if(depth[fx] < depth[fy]){
            swap(fx, fy);
            swap(x, y);
        }
        req(1, 1, s[0], s[fx], s[x]);
        x = super[fx];
        fx = top[x];
    }
    if(depth[x] > depth[y])
        swap(x, y);
    req(1, 1, s[0], s[x], s[y]);
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 1; i < n; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i = 1; i <= n; i ++)
        scanf("%d", &w[i]);
    dfsOne(1, 0);
    s[1] = ++ s[0];
    rps[s[0]] = 1;
    top[1] = 1;
    dfsTwo(1);
    con(1, 1, s[0]);
    scanf("%d", &q);
    for(int i = 0; i < q; i ++){
        AnsM = -100000000;
        AnsS = 0;
        char op[8];
        scanf("%s", op);
        if(strcmp(op, "QMAX") == 0){
            int _u, _v;
            scanf("%d%d", &_u, &_v);
            ask(_u, _v);
            printf("%d\n", AnsM);
        }
        else if(strcmp(op, "QSUM") == 0){
            int _u, _v;
            scanf("%d%d", &_u, &_v);
            ask(_u, _v);
            printf("%d\n", AnsS);
        }
        else{
            int _u, _t;
            scanf("%d%d", &_u, &_t);
            pro(1, 1, s[0], s[_u], _t);
        }
    }
    return 0;
}