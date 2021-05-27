#include <stdio.h>
#include <queue>
#pragma GCC optimize(2)
using namespace std;
int n, m;
int tab[1001][1001];
struct pos
{
	int x;
	int y;
};
queue <pos> q;
int a[100001];
int aptr;
int _ans[1001][1001];
int ans_[100001];
int ptr;
bool flg[1001][1001];
inline void write(int ans, bool bk)
{
    if(ans==0)
    {
        if(!bk)
        	putchar('0');
        return;
    }
    write(ans/10,true);
    putchar(ans%10^'0');
}
inline int read() {
    char c = getchar(); int x = 0;
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x;
}   
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			scanf("%1d", &tab[i][j]);
	for(int i = 0; i < m; i ++){
		pos p;
		int ans = 0;
		p.x = read() - 1;
		p.y = read() - 1;
		if(flg[p.x][p.y]){
			write(ans_[_ans[p.x][p.y]], false);
			putchar('\n');
			continue;
		}
		q.push(p);
		flg[p.x][p.y] = true;
		while(!q.empty()){
			ans ++;
			pos t = q.front();
			_ans[t.x][t.y] = ptr;
			flg[t.x][t.y] = true;
			int tt = tab[t.x][t.y];
			if(t.x != 0)
				if(!flg[t.x - 1][t.y] && tab[t.x - 1][t.y] != tt){
					pos _t;
					_t.x = t.x - 1;
					_t.y = t.y;
					flg[_t.x][_t.y] = true;
					q.push(_t);
				}
			if(t.y != 0)
				if(!flg[t.x][t.y - 1] && tab[t.x][t.y - 1] != tt){
					pos _t;
					_t.x = t.x;
					_t.y = t.y - 1;
					flg[_t.x][_t.y] = true;
					q.push(_t);
				}
			if(t.x != n - 1)
				if(!flg[t.x + 1][t.y] && tab[t.x + 1][t.y] != tt){
					pos _t;
					_t.x = t.x + 1;
					_t.y = t.y;
					flg[_t.x][_t.y] = true;
					q.push(_t);
				}
			if(t.y != n - 1)
				if(!flg[t.x][t.y + 1] && tab[t.x][t.y + 1] != tt){
					pos _t;
					_t.x = t.x;
					_t.y = t.y + 1;
					flg[_t.x][_t.y] = true;
					q.push(_t);
				}
			q.pop();
		}
		ans_[ptr ++] = ans;
		write(ans, false);
		putchar('\n');
	}
	return 0;
}