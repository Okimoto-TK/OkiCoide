#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct node
{
    int set;
    int dis;
    long long val;
    int lft;
    int rht;
};
int t, w;
long long k;
int n, m;
node tree[2000007];
int find(int x)
{
    if(tree[x].set == x)
    {
        return x;
    }
    else
    {
        tree[x].set = find(tree[x].set);
        return tree[x].set;
    }
}
int getDis(int x)
{
    return tree[x].rht ? tree[tree[x].rht].dis + 1 : 0;
}
int merge(int a, int b)
{
    if(!(a && b))
    {
        return a + b;
    }
    if(tree[a].val < tree[b].val)
    {
        swap(a, b);
    }
    tree[a].rht = merge(tree[a].rht, b);
    tree[tree[a].rht].set = a;
    if(tree[tree[a].lft].dis < tree[tree[a].rht].dis)
    {
        swap(tree[a].lft, tree[a].rht);
    }
    tree[a].dis = getDis(a);
    return a;
}
int remove(int x)
{
    tree[tree[x].lft].set = tree[x].lft;
    tree[tree[x].rht].set = tree[x].rht;
    int lft = tree[x].lft;
    int rht = tree[x].rht;
    tree[x].rht = tree[x].lft = tree[x].dis = 0;
    return merge(lft, rht);
}
int main()
{
    scanf("%d%d%lld", &t, &w, &k);
    while(t--)
    {
        memset(tree, 0, sizeof(tree));
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++)
        {
            scanf("%lld", &tree[i].val);
            tree[i].set = i;
        }
        for(int i = 1; i <= m; i++)
        {
            int opt;
            scanf("%d", &opt);
            if(opt == 2)
            {
                int a;
                scanf("%d", &a);
                tree[a].val = 0;
                int tmp = remove(a);
                merge(tmp, find(a));
            }
            else if(opt == 3)
            {
                int a;
                long long b;
                scanf("%d%lld", &a, &b);
                a = find(a);
                tree[a].val = max(tree[a].val - b, 0ll);
                int tmp = remove(a);
                merge(tmp, a);
            }
            else
            {
                int a, b;
                scanf("%d%d", &a, &b);
                if(a == b)
                {
                    continue;
                }
                merge(find(a), find(b));
            }
        }
        long long sum = 0, mx = 0;
        for(int i = 1; i <= n; i++)
        {
            if(tree[i].set == i)
            {
                sum += tree[i].val;
                mx = max(mx, tree[i].val);
            }
        }
        if(w == 2)
        {
            sum -= mx;
        }
        else if(w == 3)
        {
            sum += mx;
        }
        if(sum == 0)
        {
            printf("Gensokyo ");
        }
        else if(sum <= k)
        {
            printf("Heaven ");
        }
        else
        {
            printf("Hell ");
        }
        printf("%lld\n", sum);
    }
}
