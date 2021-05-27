#include <stdio.h>
#include <math.h>
using namespace std;
int n;
double l, r;
double a[16];
double calc(double x){
    double r = 0;
    for(int i = n; i >= 0; i --){
        r += pow(x, i) * a[i];
    }
    return r;
}
int main(){
    scanf("%d", &n);
    scanf("%lf %lf", &l, &r);
    for(int i = n; i >= 0; i --){
        scanf("%lf", &a[i]);
    }
    while(r - l >= 0.000001){
        double ly = calc(l);
        double ry = calc(r);
        double x1 = (r - l) / 3 + l;
        double x2 = 2 * (r - l) / 3 + l;
        double y1 = calc(x1);
        double y2 = calc(x2);
        if(ry >= y2){
            l = x2;
        }
        else if(ly >= y1){
            r = x1;
        }
        else if(y1 >= y2 && y2 >= ry){
            r = x2;
        }
        else{
            l = x1;
        }
    }
    printf("%.5f", l);
    return 0;
}
