#include <stdio.h>
#include <algorithm>
using namespace std;
struct node
{
    int val;
    int lft;
    int rht;
    int spr;
    int dis;
};
int n, m;
node tree[1000007];
int find(int x)
{
    if(tree[x].spr == x)
    {
        return x;
    }
    else
    {
        tree[x].spr = find(tree[x].spr);
        return tree[x].spr;
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
    if(tree[a].val > tree[b].val)
    {
        swap(a, b);
    }
    tree[a].rht = merge(tree[a].rht, b);
    tree[tree[a].rht].spr = a;
    if(tree[tree[a].lft].dis < tree[tree[a].rht].dis)
    {
        swap(tree[a].lft, tree[a].rht);
    }
    tree[a].dis = getDis(a);
    return a;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &tree[i].val);
        tree[i].spr = i;
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        char opt[2];
        scanf("%s", opt);
        if(opt[0] == 'M')
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if(tree[x].val == -1 || tree[y].val == -1)
            {
                continue;
            }
            if(find(x) == find(y))
            {
                continue;
            }
            merge(find(x), find(y));
        }
        else
        {
            int x;
            scanf("%d", &x);
            if(tree[x].val == -1)
            {
                printf("0\n");
                continue;
            }
            x = find(x);
            printf("%d\n", tree[x].val);
            tree[x].val = -1;
            tree[tree[x].lft].spr = tree[x].lft;
            tree[tree[x].rht].spr = tree[x].rht;
            tree[x].spr = merge(tree[x].lft, tree[x].rht);
            tree[x].lft = 0;
            tree[x].rht = 0;
        }
    }
    return 0;
}
