#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct pos
{
	int x;
	int y;
};
int x3;
int y3;
int x2;
int y2;
int n;
pos node[100007];
bool cmp(pos a, pos b){
	int adis = pow(a.x - x3, 2) + pow(a.y - y3, 2);
	int bdis = pow(b.x - x3, 2) + pow(b.y - y3, 2);
	return adis > bdis;
}
int getMin(int a, int b){
	return a < b ? a : b;
}
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	// freopen("IN.IN", "r", stdin);
	scanf("%d%d%d%d", &x3, &y3, &x2, &y2);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d%d", &node[i].x, &node[i].y);
	sort(node, node + n, cmp);
	int min = 10e9;
	int max = 0;
	for(int i = 0; i < n; i ++){
		int w = pow(node[i].x - x3, 2) + pow(node[i].y - y3, 2) + max;
		min = getMin(w, min);
		max = getMax(max, pow(node[i].x - x2, 2) + pow(node[i].y - y2, 2));
	}
	min = getMin(min, max);
	printf("%d", min);
	return 0;
}