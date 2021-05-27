
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
using namespace std;
int n;
double sx, sy, sz, ex, ey, ez;
double getAbs(double a){
    return a > 0 ? a : -a;
}
double getMin(double a, double b){
    return a < b ? a : b;
}
double r[6];
double a[6][3];
double getDis(int i, int j){
    return (sqrt(pow(a[i][0] - a[j][0], 2) + pow(a[i][1] - a[j][1], 2) + pow(a[i][2] - a[j][2], 2)) - r[j]);
}
double ans;
int t;
bool u[6];
void dfs(double s){
    if(s > ans){
        ans = s;
    }
    for(int i = 0; i < n; i ++){
        if(u[i]){
            continue;
        }
        double d = getAbs(a[i][0] - sx);
        d = getMin(d, getAbs(a[i][1] - sy));
        d = getMin(d, getAbs(a[i][2] - sz));
        d = getMin(d, getAbs(ex - a[i][0]));
        d = getMin(d, getAbs(ey - a[i][1]));
        d = getMin(d, getAbs(ez - a[i][2]));
        for(int j = 0; j < n; j ++){
            if(i == j || !u[j]){
                continue;
            }
            d = getMin(d, getDis(i, j));
        }
        if(d > 0){
            u[i] = true;
            r[i] = d;
            dfs(s + 4.0 * M_PI * pow(d, 3) / 3.0);
            r[i] = 0;
            u[i] = false;
        }
    }
}
int main(){
    scanf("%d", &n);
    while(n != 0){
        double x, y, z;
        ans = 0;
        memset(a, 0, sizeof(a));
        memset(r, 0, sizeof(r));
        memset(u, 0, sizeof(u));
        scanf("%lf%lf%lf", &sx, &sy, &sz);
        scanf("%lf%lf%lf", &ex, &ey, &ez);
        for(int i = 0; i < n; i ++){
            scanf("%lf%lf%lf", &x, &y, &z);
            a[i][0] = x;
            a[i][1] = y;
            a[i][2] = z;
        }
        dfs(0);
        printf("Box %d: %.0lf\n\n", ++ t, getAbs((ex - sx) * (ey - sy) * (ez - sz)) - round(ans));
        scanf("%d", &n);
    }
    return 0;
}
