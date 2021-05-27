#include <stdio.h>
#include <math.h>
#include <algorithm>
#define MAX 1000007
using namespace std;
struct query
{
    int l;
    int r;
    int bl;
    int id;
} q[MAX];
int n, m, blocksize;
int a[MAX];
int ans[MAX];
int cnt[MAX];
inline bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    if(a.bl & 1)
    {
        return a.r < b.r;
    }
    return a.r > b.r;
}
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void write( int x )
{
    if( x<0 ) putchar('-'), x=-x;
    if( x>9 ) write( x/10 );
    putchar(x%10+'0');
}

int main()
{
    scanf("%d", &n);
    blocksize = 1652;
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        q[i].l = read();
        q[i].r = read();
        q[i].bl = (q[i].l - 1) / blocksize + 1;
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m, cmp);
    register int l = 1;
    register int r = 0;
    int tmp = 0;
    int ll, rr;
    for(register int i = 1; i <= m; i++)
    {
        ll = q[i].l;
        rr = q[i].r;
        while(l < ll)
        {
            if(--cnt[a[l++]] == 0)
            {
                tmp--;
            }
        }
        while(l > ll)
        {
            if(cnt[a[--l]]++ == 0)
            {
                tmp++;
            }
        }
        while(r < rr)
        {
            if(cnt[a[++r]]++ == 0)
            {
                tmp++;
            }
        }
        while(r > rr)
        {
            if(--cnt[a[r--]] == 0)
            {
                tmp--;
            }
        }
        ans[q[i].id] = tmp;
    }
    for(register int i = 1; i <= m; i++)
    {
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}
