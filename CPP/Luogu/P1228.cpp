#include <stdio.h>
#include <math.h>
using namespace std;
bool map[2048][2048];
int k;
int x, y;
void func(int sx, int sy, int ex, int ey, bool flag){
	if(sx == ex)
		return;
	int mx = (ex + sx) / 2;
	int my = (ey + sy) / 2;
	if(!flag){
		if(map[sx][sy]){
			func(sx, sy, mx, my, false);
			printf("%d %d %d\n", mx + 1, my + 1, 1);
			map[mx][my + 1] = true;
			map[mx + 1][my] = true;
			map[mx + 1][my + 1] = true;
			func(sx, my + 1, mx, ey, false);
			func(mx + 1, sy, ex, my, false);
			func(mx + 1, my + 1, ex, ey, false);
		}
		else if(map[sx][ey]){
			func(sx, my + 1, mx, ey, false);
			printf("%d %d %d\n", mx + 1, my, 2);
			map[mx][my] = true;
			map[mx + 1][my] = true;
			map[mx + 1][my + 1] = true;
			func(mx + 1, sy, ex, my, false);
			func(sx, sy, mx, my, false);
			func(mx + 1, my + 1, ex, ey, false);
		}
		else if(map[ex][sy]){
			func(mx + 1, sy, ex, my, false);
			printf("%d %d %d\n", mx, my + 1, 3);
			map[mx][my + 1] = true;
			map[mx][my] = true;
			map[mx + 1][my + 1] = true;
			func(sx, my + 1, mx, ey, false);
			func(sx, sy, mx, my, false);
			func(mx + 1, my + 1, ex, ey, false);
		}
		else{
			func(mx + 1, my + 1, ex, ey, false);
			printf("%d %d %d\n", mx, my, 4);
			map[mx][my] = true;
			map[mx + 1][my] = true;
			map[mx][my + 1] = true;
			func(mx + 1, sy, ex, my, false);
			func(sx, sy, mx, my, false);
			func(sx, my + 1, mx, ey, false);
		}
	}
	else{
		if((sx <= x && x <= mx) && (sy <= y && y <= my)){
			func(sx, sy, mx, my, true);
			printf("%d %d %d\n", mx + 1, my + 1, 1);
			map[mx][my + 1] = true;
			map[mx + 1][my] = true;
			map[mx + 1][my + 1] = true;
			func(mx + 1, my + 1, ex, ey, false);
			func(mx + 1, sy, ex, my, false);
			func(sx, my + 1, mx, ey, false);
		}
		else if((sx <= x && x <= mx) && (ey >= y && y > my)){
			func(sx, my + 1, mx, ey, true);
			printf("%d %d %d\n", mx + 1, my, 2);
			map[mx][my] = true;
			map[mx + 1][my] = true;
			map[mx + 1][my + 1] = true;
			func(mx + 1, my + 1, ex, ey, false);
			func(mx + 1, sy, ex, my, false);
			func(sx, sy, mx, my, false);
		}
		else if((ex >= x && x > mx) && (sy <= y && y <= my)){
			func(mx + 1, sy, ex, my, true);
			printf("%d %d %d\n", mx, my + 1, 3);
			map[mx][my + 1] = true;
			map[mx][my] = true;
			map[mx + 1][my + 1] = true;
			func(mx + 1, my + 1, ex, ey, false);
			func(sx, my + 1, mx, ey, false);
			func(sx, sy, mx, my, false);
		}
		else{
			func(mx + 1, my + 1, ex, ey, true);
			printf("%d %d %d\n", mx, my, 4);
			map[mx][my] = true;
			map[mx + 1][my] = true;
			map[mx][my + 1] = true;
			func(mx + 1, sy, ex, my, false);
			func(sx, my + 1, mx, ey, false);
			func(sx, sy, mx, my, false);
		}
	}
}
int main(int argc, char const *argv[])
{
	scanf("%d", &k);
	scanf("%d%d", &x, &y);
	map[x][y] = true;
	func(1, 1, pow(2, k), pow(2, k), true);
	return 0;
}