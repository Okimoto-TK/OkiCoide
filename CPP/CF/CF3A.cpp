#include <stdio.h>
#include <string>
using namespace std;
char fx;
int fy;
char ex;
int ey;
int dx, dy;
int f, e;
string ans;
int cnt;
int main(int argc, char const *argv[])
{
	scanf("%c%d\n", &fx, &fy);
	scanf("%c%d", &ex, &ey);
	f = fx - 'a';
	e = ex - 'a';
	fy -= 1;
	ey -= 1;
	dx = f - e;
	dy = fy - ey;
	while(dx != 0 || dy != 0){
		cnt ++;
		if(dx > 0){
			dx --;
			ans += "L";
		}
		else if(dx < 0){
			dx ++;
			ans += "R";
		}
		if(dy > 0){
			dy --;
			ans += "D";
		}
		else if(dy < 0){
			dy ++;
			ans += "U";
		}
		ans += "\n";
	}
	printf("%d\n%s", cnt, ans.c_str());
	return 0;
}