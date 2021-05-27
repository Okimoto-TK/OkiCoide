#include <stdio.h>
using namespace std;
int p;
int prm[100007];
bool is[1000007];
int main(int argc, char const *argv[]) {
    //pre
    for(int i = 2; i <= 1000000; i ++){
        if(!is[i]){
            prm[p ++] = i;
        }
        for(int j = 0; j < p && prm[j] * i <= 1000000; j ++){
            is[prm[j] * i] = true;
        }
    }
    //proc
    int n;
    scanf("%d", &n);
    while(n != 0){
        for(int i = 0; i < p; i ++){
            if(!is[n - prm[i]]){
                printf("%d = %d + %d\n", n, prm[i], n - prm[i]);
                break;
            }
        }
        scanf("%d", &n);
    }
    return 0;
}
