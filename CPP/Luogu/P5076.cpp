#include <stdio.h>
using namespace std;
struct node
{
    int vl;
    int ch[2];
    int cn;
    int sz;
    int sp;
};
int n, rt, p;
node t[200007];
inline void upd(const int &k){ t[k].sz = t[t[k].ch[0]].sz + t[t[k].ch[1]].sz + t[k].cn; }
inline void rot(int x)
{
    int y = t[x].sp;
    int z = t[y].sp;
    int k = t[y].ch[1] == x;
    t[z].ch[t[z].ch[1] == y] = x;
    t[x].sp = z;
    t[y].ch[k] = t[x].ch[k ^ 1];
    t[t[x].ch[k ^ 1]].sp = y;
    t[x].ch[k ^ 1] = y;
    t[y].sp = x;
    upd(x);
    upd(y);
}
inline void spl(int x, const int &v)
{
    while(t[x].sp != v)
    {
        int y = t[x].sp;
        int z = t[y].sp;
        if(z != v){ ((t[z].ch[0] == y) ^ (t[y].ch[0] == x)) ? rot(x) : rot(y); }
        rot(x);
    }
    if(v == 0){ rt = x; }
}
void fnd(const int &v)
{
    int k = rt;
    if(!k){ return; }
    while(t[k].ch[v > t[k].vl] && v != t[k].vl){ k = t[k].ch[v > t[k].vl]; }
    spl(k, 0);
}
void ins(const int &v)
{
    int k = rt;
    int s = 0;
    while(k && t[k].vl != v)
    {
        s = k;
        k = t[k].ch[v > t[k].vl];
    }
    if(k){ ++t[k].cn; }
    else
    {
        k = ++p;
        t[k].vl = v;
        t[k].ch[1] = 0;
        t[k].ch[0] = 0;
        if(s){ t[s].ch[v > t[s].vl] = k; }
        t[k].sp = s;
        t[k].cn = 1;
        t[k].sz = 1;
    }
    spl(k, 0);
}
int pre(const int v)
{
    fnd(v);
    int k = rt;
    if(t[k].vl < v){ return k; }
    k = t[k].ch[0];
    while(t[k].ch[1]){ k = t[k].ch[1]; }
    return k;
}
int suf(const int v)
{
    fnd(v);
    int k = rt;
    if(t[k].vl > v){ return k; }
    k = t[k].ch[1];
    while(t[k].ch[0]){ k = t[k].ch[0]; }
    return k;
}
int kth(int k)
{
    int x = rt;
    while(k && x)
    {
        //printf("%d\n", x);
        if(t[t[x].ch[0]].sz >= k){ x = t[x].ch[0]; }
        else if(t[t[x].ch[0]].sz + t[x].cn >= k){ return t[x].vl; }
        else
        {
            k -= t[t[x].ch[0]].sz + t[x].cn;
            x = t[x].ch[1];
        }
    }
    return 0;
}
int rnk(const int &k)
{
    fnd(k);
    int x = rt;
    int res = 0;
    //printf("----\n");
    while(x)
    {
        //printf("%d\n", res);
        if(k < t[x].vl){ x = t[x].ch[0]; }
        else if(k == t[x].vl){ return res + t[t[x].ch[0]].sz; }
        else
        {
            res += t[t[x].ch[0]].sz + t[x].cn;
            x = t[x].ch[1];
        }
    }
    //printf("---\n");
    return res;
}
int main()
{
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    scanf("%d", &n);
    ins(-2147483647);
    ins(2147483647);
    for(int i = 0; i < n; i++)
    {
        int opt, x;
        scanf("%d %d", &opt, &x);
        if(opt == 5){ ins(x); }
        if(opt == 1){ printf("%d\n", rnk(x)); }
        if(opt == 2){ printf("%d\n", kth(x + 1)); }
        if(opt == 3){ printf("%d\n", t[pre(x)].vl); }
        if(opt == 4){ printf("%d\n", t[suf(x)].vl); }
    }
    return 0;
}
