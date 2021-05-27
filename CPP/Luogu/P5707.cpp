#include <cstdio>
#include <cmath>
struct time
{
    int hr;
    int min;
    time()
    {
        hr = 8;
        min = 0;
    }
    void minus(int x)
    {
        for(int i = 1; i <= x; i++)
        {
            if(--min == -1)
            {
                min = 59;
                if(--hr == -1) hr = 23;
            }
        }
    }
    void print()
    {
        printf("%1d%1d:%1d%1d\n", hr / 10, hr % 10, min / 10, min % 10);
    }
} timer;
int main()
{
    int s, v;
    scanf("%d%d", &s, &v);
    timer.minus((int)ceil(double(s) / double(v)) + 10);
    timer.print();
    return 0;
}
