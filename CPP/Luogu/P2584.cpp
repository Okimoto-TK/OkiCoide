#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <string>
using namespace std;
struct node
{
    double vl;
    int lc;
    int rc;
    int pr;
    int sz;
    int id;
};
int n, p, rt, ptr, size;
node t[250007];
map <int, double> rec;
map <string, double> last;
map <string, int> mapid;
map <int, string> mapstr;
void upd(const int &k)
{
    t[k].sz = t[t[k].lc].sz + t[t[k].rc].sz + 1;
}
void zig(int &k)
{
    int y = t[k].lc;
    t[k].lc = t[y].rc;
    t[y].rc = k;
    t[y].sz = t[k].sz;
    upd(k);
    k = y;
}
void zag(int &k)
{
    int y = t[k].rc;
    t[k].rc = t[y].lc;
    t[y].lc = k;
    t[y].sz = t[k].sz;
    upd(k);
    k = y;
}
void ins(int &k, const double &v, const int &i)
{
    if(k == 0)
    {
        k = ++p;
        t[k].lc = 0;
        t[k].rc = 0;
        t[k].vl = v;
        t[k].sz = 1;
        t[k].id = i;
        t[k].pr = rand();
        size++;
        return;
    }
    t[k].sz++;
    if(v > t[k].vl)
    {
        ins(t[k].lc, v, i);
        upd(k);
        if(t[t[k].lc].pr < t[k].pr)
        {
            zig(k);
        }
    }
    else
    {
        ins(t[k].rc, v, i);
        upd(k);
        if(t[t[k].rc].pr < t[k].pr)
        {
            zag(k);
        }
    }
}
void del(int &k, const double &v)
{
    if(v == 0 || k == 0)
    {
        return;
    }
    upd(k);
    if(v == t[k].vl)
    {
        if(t[k].lc == 0 || t[k].rc == 0)
        {
            size--;
            k = t[k].lc + t[k].rc;
        }
        else if(t[t[k].lc].pr < t[t[k].rc].pr)
        {
            zig(k);
            del(k, v);
        }
        else
        {
            zag(k);
            del(k, v);
        }
        return;
    }
    t[k].sz --;
    if(v > t[k].vl)
    {
        del(t[k].lc, v);
    }
    else
    {
        del(t[k].rc, v);
    }
}
int rnk(const double &v)
{
    int x = rt;
    int res = 0;
    while(x)
    {
        upd(x);
        if(v == t[x].vl)
        {
            return res + t[t[x].lc].sz + 1;
        }
        if(v > t[x].vl)
        {
            x = t[x].lc;
        }
        else
        {
            res += t[t[x].lc].sz + 1;
            x = t[x].rc;
        }
    }
}
int kth(int k)
{
    //printf("Start\n");
    int x = rt;
    while(x)
    {
        if(t[t[x].lc].sz >= k)
        {
            x = t[x].lc;
        }
        else if(t[t[x].lc].sz + 1 == k)
        {
            return t[x].id;
        }
        else
        {
            k -= t[t[x].lc].sz;
            k -= 1;
            x = t[x].rc;
        }
    }
    //printf("End!\n");
    return 0;
}
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        char opt[2];
        char tp[16];
        scanf("%1s", opt);
        scanf("%s", tp);
        string tmp = tp;
        if(opt[0] == '+')
        {
            int v;
            scanf("%d", &v);
            double x = last[tmp];
            del(rt, x);
            x = v;
            if(rec[v] == 0)
            {
                rec[v] = 1;
            }
            rec[v] -= 0.000001;
            x += rec[v];
            mapid[tmp] = ++ptr;
            mapstr[ptr] = tmp;
            ins(rt, x, ptr);
            last[tmp] = x;
        }
        else if(tmp[0] > '9')
        {
            double v = last[tmp];
            printf("%d\n", rnk(v));
        }
        else
        {
            int x = 0;
            for(int j = 0; j < tmp.size(); j++)
            {
                x *= 10;
                x += tmp[j] - '0';
            }
            for(int j = x; j < x + 10 && j <= size; j++)
            {
                printf("%s ", mapstr[kth(j)].c_str());
            }
            printf("\n");
        }
    }
    return 0;
}
