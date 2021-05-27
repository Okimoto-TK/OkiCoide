#include <stdio.h>
#include <algorithm>
using namespace std;
struct node
{
    int super;
    int left;
    int right;
    int value;
    int dist;
    bool del;
};
node tree[100007];
int n, m;
int getDist(int x)
{
    if(tree[x].right)
    {
        return tree[tree[x].right].dist + 1;
    }
    else
    {
        return 0;
    }
}
int find(int a)
{
    if(tree[a].super != a)
    {
        tree[a].super = find(tree[a].super);
        return tree[a].super;
    }
    else
    {
        return a;
    }
}
int merge(int a, int b, int x, int y)
{
    if(a == 0)
    {
        return b;
    }
    if(b == 0)
    {
        return a;
    }
    int r = x;
    if(tree[a].value > tree[b].value || (tree[a].value == tree[b].value && a > b))
    {
        swap(a, b);
        r = y;
    }
    tree[a].right = merge(tree[a].right, b, r, r);
    tree[tree[a].right].super = a;
    if(tree[tree[a].left].dist < tree[tree[a].right].dist)
    {
        swap(tree[a].left, tree[a].right);
    }
    tree[a].dist = getDist(a);
    return a;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &tree[i].value);
        tree[i].super = i;
    }
    for(int i = 1; i <= m; i++)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if(find(x) == find(y))
            {
                continue;
            }
            if(tree[x].del || tree[y].del)
            {
                continue;
            }
            merge(find(x), find(y), find(x), find(y));
        }
        else
        {
            int x;
            scanf("%d", &x);
            if(tree[x].del)
            {
                printf("-1\n");
                continue;
            }
            x = find(x);
            printf("%d\n", tree[x].value);
            tree[x].value = -1;
            tree[x].del = true;
            tree[tree[x].left].super = tree[x].left;
            tree[tree[x].right].super = tree[x].right;
            tree[x].super = merge(tree[x].left, tree[x].right, tree[x].left, tree[x].right);
            tree[x].right = 0;
            tree[x].left = 0;
        }
    }
    return 0;
}
