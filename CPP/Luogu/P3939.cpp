#include <cstdio>
#include <algorithm>
#define N 300007
inline int read(){  
   int s=0,w=1;  
   char ch=getchar();  
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}  
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();  
   return s*w;  
} 
inline void write(int x)
{
    char ch[20];
    int len=0;
    //ch里面存的是从低到高的数字的ASCLL码 len是数组长度 
    if(x<0)//如果x是负数，那么先输出负号，再把x变成正数 
      {
        putchar((1<<5)+(1<<3)+(1<<2)+1);
        //(1<<5)+(1<<3)+(1<<2)+1就是'-'的ASCLL码值 
        x=~x+1;//x=~x+1;就等同于x=-x;
      }
    do//用do while可以防止x=0的特殊情况 
      {
        ch[len++]=x%10+(1<<4)+(1<<5);//取出最低位存到ch数组里面 因为ch是字符数组，所以要加上0的ASCLL码 
        x/=10;//砍掉最低位 
      }while(x>0);//当x>0的时候每次把x的最低位取出 
    for(int i=len-1;i>=0;i--)//因为ch是从低到高存的x的绝对值，又因为要从高到低输出，所以倒着循环ch数组输出 
       putchar(ch[i]);//输出从高到低的每一位 
    putchar('\n');
    return ;
} 
int n, m, pool;
int a[N];
int rt[N];
struct node
{
    int lc;
    int rc;
    int vl;
    node() { lc = rc = vl = 0; };
} t[20000000];
void push_up(int k) { t[k].vl = t[t[k].lc].vl + t[t[k].rc].vl; }
int build(int l, int r)
{
    int k = ++pool;
    if(l == r)  return k;
    int mid = (l + r) >> 1;
    t[k].lc = build(l, mid);
    t[k].rc = build(mid + 1, r);
    push_up(k);
    return k;
}
int insert(int _k, int l, int r, int x, int v)
{
    int k = ++pool;
    if(l == r)
    {
        t[k].vl = t[_k].vl + v;
        return k;
    }
    t[k].lc = t[_k].lc;
    t[k].rc = t[_k].rc;
    int mid = (l + r) >> 1;
    if(x <= mid) t[k].lc = insert(t[k].lc, l, mid, x, v);
    else t[k].rc = insert(t[k].rc, mid + 1, r, x, v);
    push_up(k);
    return k;
}
int query(int k, int l, int r, int x)
{
    if(l == r) return t[k].vl;
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid) res += query(t[k].lc, l, mid, x);
    else res += query(t[k].rc, mid + 1, r, x);
    return res;
}
inline int get()
{
    int l = read(), r = read(), c = read();
    return query(rt[r], 1, N, c) - query(rt[l - 1], 1, N, c);
}
inline void set()
{
    int x = read();
    rt[x] = insert(rt[x], 1, N, a[x], -1);
    rt[x] = insert(rt[x], 1, N, a[x + 1], 1);
    std::swap(a[x], a[x + 1]);
}
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d", &n, &m);
    rt[0] = build(1, N);
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
        rt[i] = insert(rt[i - 1], 1, N, a[i], 1);   
    }    
    for(; m != 0; m--)
    {
        int opt;
        opt = read();
        if(opt == 1) write(get());
        if(opt == 2) set();
    }
    return 0;
}
