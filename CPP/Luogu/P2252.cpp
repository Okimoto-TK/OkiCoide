#include <stdio.h>
#include <math.h>
using namespace std;
int main(){
    const double s= (sqrt(5) + 1.0) / 2.0;
    int a, b;
    scanf("%d%d", &a, &b);
    if(a < b){
        int t = a;
        a = b;
        b = t;
    }
    a -= b;
    if(int(a * s) == b){
        printf("0");
    }
    else{
        printf("1");
    }
    return 0;
}
