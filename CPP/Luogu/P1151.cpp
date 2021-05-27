#include <stdio.h>
using namespace std;
int k;
bool chk(int x){
    int s1 = x / 100;
    int s2 = (x % 10000) / 10;
    int s3 = x % 1000;
    if(s1 % k == 0 && s2 % k == 0 && s3 % k == 0){
        return true;
    }
    return false;
}
int main(){
    bool have = false;
    scanf("%d", &k);
    for(int i = 10000; i <= 30000; i ++){
        if(chk(i)){
            have = true;
            printf("%d\n", i);
        }
    }
    if(!have){
        printf("No");
    }
    return 0;
}
