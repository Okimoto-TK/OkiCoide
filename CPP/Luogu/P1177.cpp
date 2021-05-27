#include <stdio.h>
#include <stdlib.h>
using namespace std;
int arr[100001];
void mineSwap(int & a, int & b){
	int temp = a;
	a = b;
	b = temp;
}
void quickSort(int l, int r){
	int i = l, j = r;
	int mid = arr[rand() % (r - l + 1) + l];
	do{
		while(arr[i] < mid) i ++;
		while(arr[j] > mid) j --;
		if(i <= j){
			mineSwap(arr[i], arr[j]);
			i ++;
			j --;
		}
	}while(i <= j);
	if(j > l) quickSort(l, j);
	if(i < r) quickSort(i, r);
}
int main(int argc, char const *argv[])
{
	int l;
	scanf("%d", &l);
	for(int i = 0; i < l; i ++){
		scanf("%d", &arr[i]);
	}
	quickSort(0, l - 1);
	for(int i = 0; i < l; i ++){
		printf("%d ", arr[i]);
	}
	return 0;
}