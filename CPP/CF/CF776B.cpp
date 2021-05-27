#include <stdio.h>
#include <vector>
using namespace std;
int n, p;
bool is[100007];
int prm[100007];
bool to[100007];
bool yesh;
vector <int> pfr[100007];
int main(){
    scanf("%d", &n);
    for(int i = 2; i <= n + 1; i ++){
        if(!is[i]){
            prm[p ++] = i;
        }
        for(int j = 0; j < p && i * prm[j] <= n + 1; j ++){
            is[i * prm[j]] = true;
        }
    }
    for(int i = 0; i < p; i ++){
        for(int j = 2; j * prm[i] <= n + 1; j ++){
            int k = j * prm[i];
            to[prm[i]] = true;
            pfr[k].push_back(prm[i]);
            yesh = true;
        }
    }
    if(yesh)
        printf("2\n");
    else
        printf("1\n");
    for(int i = 2; i <= n + 1; i ++){
        printf("%d ", !is[i] && to[i] ? 2 : 1);
    }
}
