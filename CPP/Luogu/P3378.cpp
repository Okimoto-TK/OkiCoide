#include <stdio.h>
#include <queue>
using namespace std;
int heap[1000001];
int len;
int n;
queue <int> ans;
void swap(int & a, int & b){
	int temp = a;
	a = b;
	b = temp;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		int op;
		scanf("%d", &op);
		if(op == 1){
			int x;
			scanf("%d", &x);
			heap[++ len] = x;
			int pos = len;
			while(heap[pos] < heap[pos / 2]){
				swap(heap[pos], heap[pos / 2]);
				pos /= 2;
			}
		}
		else if(op == 2){
			ans.push(heap[1]);
		}
		else if(op == 3){
			swap(heap[1], heap[len]);
			len --;
			int pos = 1;
			while(true){
				if(2 * pos > len)
					break;
				if(2 * pos + 1 > len){
					if(heap[pos] > heap[2 * pos]){
						swap(heap[pos], heap[2 * pos]);
						pos *= 2;
					}
					else
						break;
				}
				else{
					int min = heap[2 * pos] > heap[2 * pos + 1] ? heap[2 * pos + 1] : heap[2 * pos];
					int ptr;
					if(min == heap[2 * pos])
						ptr = 2 * pos;
					else
						ptr = 2 * pos + 1;
					if(heap[pos] > min){
						swap(heap[pos], heap[ptr]);
						pos = ptr;
					}
					else
						break;
				}
			}
		}
	}
	while(!ans.empty()){
		printf("%d\n", ans.front());
		ans.pop();
	}
	return 0;
}