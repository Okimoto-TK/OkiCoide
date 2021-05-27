#include <stdio.h>
#include <queue>
#include <algorithm>
#define N 1000007
using namespace std;
int n, k;
long long tmp;
long long ans;
long long V[N];
int L[N];
int R[N];
priority_queue<pair<int, int> > heap;
bool vis[N];
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        scanf("%I64d", &V[i]);
        L[i] = i - 1;
        R[i] = i + 1;
        heap.push(pair<int, int>(V[i], i));
    }
    V[n + 1] = V[0] = -100000000000ll;
    for(int i = 1; i <= min(n, k); i++)
    {
        while(!heap.empty() && vis[heap.top().second])
        {
            heap.pop();
        }
        int vl = heap.top().first;
        int id = heap.top().second;
        heap.pop();
        tmp += vl;
        ans = max(tmp, ans);
        V[id] = vl = V[L[id]] + V[R[id]] - vl;
        vis[L[id]] = true;
        vis[R[id]] = true;
        L[id] = L[L[id]];
        R[id] = R[R[id]];
        L[R[id]] = id;
        R[L[id]] = id;
        heap.push(pair<int, int>(vl, id));
    }
    printf("%lld", ans);
    return 0;
}
