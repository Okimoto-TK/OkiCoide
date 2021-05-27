#include <stdio.h>
#include <vector>
using namespace std;
int n, p;
bool is[1000007];
vector <int> prm;
vector <int> pfr[1000007];
int tab[1000007];
long long ans = 1;
long long mod = 1000000007;
int main(){
    for(int i = 2; i <= 1000000; i ++){
        if(!is[i]){
            prm.push_back(i);
        }
        for(int j = 0; j < prm.size() && i * prm[j] <= 1000000; j ++){
            is[i * prm[j]] = true;
        }
    }
    for(int i = 0; i < prm.size(); i ++){
        for(int j = 1; prm[i] * j <= 1000000; j ++){
            int k = prm[i] * j;
            while(k % prm[i] == 0){
                pfr[prm[i] * j].push_back(prm[i]);
                k /= prm[i];
            }
        }
    }
    scanf("%d", &n);
    for(int i = 2; i <= n; i ++){
        for(int j = 0; j < pfr[i].size(); j ++){
            tab[pfr[i][j]] += 2;
        }
    }
    for(int i = 0; i <= 1000000; i ++){
        ans = ans * (tab[i] + 1) % mod;
    }
    printf("%lld", ans);
    return 0;
}
