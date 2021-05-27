#include <stdio.h>
#include <algorithm>
using namespace std;
struct node
{
    int lch;
    int rch;
    int val;
    int pri;
    int cnt;
    int siz;
};
int n, ptr;
int rt;
node t[200007];
void upd(const int & k){
    t[k].siz = t[t[k].lch].siz + t[t[k].rch].siz + t[k].cnt;
}
void zig(int & k){
    int y = t[k].lch;
    t[k].lch = t[y].rch;
    t[y].rch = k;
    t[y].siz = t[k].siz;
    upd(k);
    k = y;
}
void zag(int & k){
    int y = t[k].rch;
    t[k].rch = t[y].lch;
    t[y].lch = k;
    t[y].siz = t[k].siz;
    upd(k);
    k = y;
}
void ins(int & k, const int & v){
    if(k == 0){
        k = ++ ptr;
        t[k].siz = 1;
        t[k].cnt = 1;
        t[k].val = v;
        t[k].pri = rand() % 100000000;
        t[k].lch = 0;
        t[k].rch = 0;
        return;
    }
    else
        ++ t[k].siz;
    if(t[k].val == v)
        t[k].cnt ++;
    else if(t[k].val < v){
        ins(t[k].rch, v);
        upd(k);
        if(t[t[k].rch].pri < t[k].pri)
            zag(k);
    }
    else{
        ins(t[k].lch, v);
        upd(k);
        if(t[t[k].lch].pri < t[k].pri)
            zig(k);
    }
}
void del(int & k, const int & v){
    upd(k);
    if(t[k].val == v){
        if(t[k].cnt > 1){
            t[k].cnt --;
            t[k].siz --;
        }
        else if(t[k].lch == 0 || t[k].rch == 0)
            k = t[k].lch + t[k].rch;
        else if(t[t[k].lch].pri < t[t[k].rch].pri){
            zig(k);
            del(k, v);
        }
        else{
            zag(k);
            del(k, v);
        }
        return;
    }
    t[k].siz --;
    if(v < t[k].val)
        del(t[k].lch, v);
    else
        del(t[k].rch, v);
}
int pre(const int & v){
    int x = rt;
    int res = -100000000;
    while(x){
        upd(x);
        if(t[x].val < v){
            res = t[x].val;
            x = t[x].rch;
        }
        else
            x = t[x].lch;
    }
    return res;
}
int suf(const int & v){
    int x = rt;
    int res = 100000000;
    while(x){
        upd(x);
        if(t[x].val > v){
            res = t[x].val;
            x = t[x].lch;
        }
        else
            x = t[x].rch;
    }
    return res;
}
int kth(int k){
    int x = rt;
    while(x){
        upd(x);
        if(t[t[x].lch].siz < k && k <= t[t[x].lch].siz + t[x].cnt)
            return t[x].val;
        if(t[t[x].lch].siz >= k)
            x = t[x].lch;
        else{
            k -= t[t[x].lch].siz + t[x].cnt;
            x = t[x].rch;
        }
    }
    return 0;
}
int rnk(const int & v){
    int x = rt;
    int res = 0;
    while(x){
        upd(x);
        if(v == t[x].val)
            return res + t[t[x].lch].siz + 1;
        if(v < t[x].val)
            x = t[x].lch;
        else{
            res += t[t[x].lch].siz + t[x].cnt;
            x = t[x].rch;
        }
    }
    return res;
}
int main(int argc, char const *argv[])
{
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        int opt, x;
        scanf("%d%d", &opt, &x);
        if(opt == 1)
            ins(rt, x);
        else if(opt == 2)
            del(rt, x);
        else if(opt == 3)
            printf("%d\n", rnk(x));
        else if(opt == 4)
            printf("%d\n", kth(x));
        else if(opt == 5)
            printf("%d\n", pre(x));
        else
            printf("%d\n", suf(x));
    }
    return 0;
}