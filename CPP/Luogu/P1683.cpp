#include <stdio.h>
#include <queue>
#include <string>
using namespace std;
string map[32];
int w, h;
struct pos
{
	int x;
	int y;
};
queue <pos> q;
int main(int argc, char const *argv[])
{
	scanf("%d %d", &w, &h);
	for(int i = 0; i < h; i ++){
		char input[32];
		scanf("%s", input);
		map[i] = input;
	}
	int x, y;
	for(int i = 0; i < h; i ++){
		for(int j = 0; j < w; j ++){
			if(map[i][j] == '@'){
				x = i;
				y = j;
			}
		}
	}
	pos f;
	f.x = x;
	f.y = y;
	q.push(f);
	map[x][y] = '#';
	int ans = 1;
	while(!q.empty()){
		pos t = q.front();
		for(int i = -1; i <= 1; i ++){
			if(t.x + i < 0)
				continue;
			if(t.x + i >= h)
				continue;
			for(int j = -1; j <= 1; j ++){
				if(t.y + j < 0)
					continue;
				if(t.y + j >= w)
					continue;
				if(i != 0 && j != 0)
					continue;
				if(map[t.x + i][t.y + j] == '.'){
					f.x = t.x + i;
					f.y = t.y + j;
					q.push(f);
					map[f.x][f.y] = '#';
					ans ++;
				}
			}
		}
		q.pop();
	}
	printf("%d", ans);
	return 0;
}