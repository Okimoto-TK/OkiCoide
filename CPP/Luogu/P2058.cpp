#include <stdio.h>
#include <queue>
using namespace std;
struct psn
{
    int a;
    int x;
} p[300007];
int ans;
int n;
int ptr;
queue <psn> q;
int c[100007];
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        int t;
       	int k;
       	scanf("%d%d", &t, &k);
        for(int j = 0; j < k; j ++){
            int x;
            scanf("%d", &x);
            p[ptr].x = x;
            p[ptr].a = t;
            q.push(p[ptr]);
            c[x] ++;
            if(c[x] == 1)
                ans ++;
        }
        while(q.front().a <= t - 86400){
            c[q.front().x] --;
            if(c[q.front().x] == 0)
                ans --;
            q.pop();
        }
        printf("%d\n", ans);
    }
    return 0;
}