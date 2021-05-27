#include <stdio.h>
using namespace std;
int map[200][200];
int d;
int n;
int cnt(int x1, int y1, int x2, int y2){
    int sum = 0;
    for(int i = x1; i <= x2; i ++){
        for(int j = y1; j <= y2; j ++){
            sum += map[i][j];
        }
    }
    return sum;
}
int getMax(int a, int b){
    return a > b ? a : b;
}
int getMin(int a, int b){
    return a < b ? a : b;
}
int main(){
    scanf("%d%d", &d, &n);
    for(int i = 0; i < n; i ++){
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        map[x][y] = k;
    }
    int ans = 0;
    int max = 0;
    for(int i = 0; i < 129; i ++){
        for(int j = 0; j < 129; j ++){
            int tmp = cnt(getMax(i - d, 0), getMax(j - d, 0), getMin(i + d, 128), getMin(j + d, 128));
            if(tmp > max){
                ans = 1;
                max = tmp;
            }
            else if(tmp == max){
                ans += 1;
            }
        }
    }
    printf("%d %d", ans, max);
}