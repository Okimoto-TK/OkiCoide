#include <cstdio>
struct Carpet
{
	int a;
	int b;
	int g;
	int k;
};
Carpet cpt[10007];
int n, x, y;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d %d %d %d", &cpt[i].a, &cpt[i].b, &cpt[i].g, &cpt[i].k);
	scanf("%d %d", &x, &y);
	for(int i = n - 1; i >= 0; i--) // From the latter one to the former one. If Carpet #i is valid, print and exit.
	{
		if(cpt[i].a <= x && cpt[i].b <= y && cpt[i].a + cpt[i].g >= x && cpt[i].b + cpt[i].k >= y)
		{
			printf("%d", i + 1);
			return 0;
		}
	}
	printf("-1"); // There are no carpets covering on (x, y)
	return 0;
}
