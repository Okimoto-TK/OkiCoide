#include <stdio.h>
#include <vector>
using namespace std;
int n;
int ans[100007];
int proc[100007];
int had[1000007];
vector <int> fac[1000007];
int main(int argc, char const *argv[]){
    // pre
    for(register int i = 1; i <= 1000; i ++){
        for(register int j = i * i, k = i; j <= 1000000; j += i, k ++){
            fac[j].push_back(i);
            if(i != k){
                fac[j].push_back(k);
            }
        }
    }
    // proc
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++){
        int a;
        scanf("%d", &a);
        had[a] ++;
        proc[i] = a;
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < fac[proc[i]].size(); j ++){
            int x = fac[proc[i]][j];
            ans[i] += had[x];
        }
    }
    // suf
    for(int i = 0; i < n; i ++){
        printf("%d\n", ans[i] - 1);
    }
    return 0;
}
