#include <stdio.h>
#include <algorithm>
#include <string.h>
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
node tree[100007];
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
    return tree[x].rht ? tree[x].rht + 1 : 0;
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
    tree[tree[a].rht].spr = a;
    if(tree[tree[a].lft].dis < tree[tree[a].rht].dis)
    {
        swap(tree[a].lft, tree[a].rht);
    }
    tree[a].dis = getDis(a);
    return a;
}
int remove(int x)
{
    tree[tree[x].lft].spr = tree[x].lft;
    tree[tree[x].rht].spr = tree[x].rht;
    int lft = tree[x].lft;
    int rht = tree[x].rht;
    tree[x].rht = tree[x].lft = tree[x].dis = 0;
    return merge(lft, rht);
}
int main()
{
    while(scanf("%d", &n) != EOF)
    {
        memset(tree, 0, sizeof(tree));
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &tree[i].val);
            tree[i].spr = i;
        }
        scanf("%d", &m);
        for(int i = 1; i <= m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if(find(x) == find(y))
            {
                printf("-1\n");
                continue;
            }
            int _x = find(x);
            int _y = find(y);
            int tmp = remove(_x);
            tree[_x].val /= 2;
            int _tmp = remove(_y);
            tree[_y].val /= 2;
            merge(_x, tmp);
            merge(_y, _tmp);
            merge(find(_x), find(_y));
            printf("%d\n", tree[find(_x)].val);
        }
    }
    return 0;
}
