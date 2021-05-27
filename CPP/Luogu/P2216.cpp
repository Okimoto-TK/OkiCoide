#include <stdio.h>
#include <deque>
using namespace std;
int a, b, n;
int num[1024][1024];
int grtr[1024][1024];
int less[1024][1024];
int _grtr[1024][1024];
int grtr_[1024][1024];
int _less[1024][1024];
int less_[1024][1024];
deque <int> d[1024];
bool init[1024];
int ans = 1000000000;
int getMin(int a, int b){
	return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d%d%d", &a, &b, &n);
	for(int i = 0; i < a; i ++)
		for(int j = 0; j < b; j ++)
			scanf("%d", &num[i][j]);
	for(int i = 0; i < a; i ++){
		for(int j = 0; j < b; j ++){
			if(!init[i]){
				d[i].push_back(j);
				init[i] = true;
			}
			else{
				while(!d[i].empty() && num[i][j] >= num[i][d[i].back()])
					d[i].pop_back();
				d[i].push_back(j);
				if(d[i].front() <= j - n)
					d[i].pop_front();
			}
			grtr[i][j] = d[i].front();
		}
		d[i].clear();
		init[i] = false;
	}
	for(int i = 0; i < a; i ++){
		for(int j = 0; j < b; j ++){
			if(!init[i]){
				d[i].push_back(j);
				init[i] = true;
			}
			else{
				while(!d[i].empty() && num[i][j] <= num[i][d[i].back()])
					d[i].pop_back();
				d[i].push_back(j);
				if(d[i].front() <= j - n)
					d[i].pop_front();
			}
			less[i][j] = d[i].front();
		}
		d[i].clear();
		init[i] = false;
	}
	for(int j = 0; j < b; j ++){
		for(int i = 0; i < a; i ++){
			if(!init[j]){
				d[j].push_back(i);
				init[j] = true;
			}
			else{
				while(!d[j].empty() && num[i][grtr[i][j]] >= num[d[j].back()][grtr[d[j].back()][j]])
					d[j].pop_back();
				d[j].push_back(i);
				if(d[j].front() <= i - n)
					d[j].pop_front();
			}
			_grtr[i][j] = d[j].front();
		}
		d[j].clear();
		init[j] = false;
	}
	for(int j = 0; j < b; j ++){
		for(int i = 0; i < a; i ++){
			if(!init[j]){
				d[j].push_back(i);
				init[j] = true;
			}
			else{
				while(!d[j].empty() && num[i][less[i][j]] <= num[d[j].back()][less[d[j].back()][j]])
					d[j].pop_back();
				d[j].push_back(i);
				if(d[j].front() <= i - n)
					d[j].pop_front();
			}
			_less[i][j] = d[j].front();
		}
		d[j].clear();
		init[j] = false;
	}
	for(int i = n - 1; i < a; i ++){
		for(int j = n - 1; j < b; j ++){
			ans = getMin(ans, num[_grtr[i][j]][grtr[_grtr[i][j]][j]] - num[_less[i][j]][less[_less[i][j]][j]]);
		}
	}
	printf("%d", ans);
	return 0;
}