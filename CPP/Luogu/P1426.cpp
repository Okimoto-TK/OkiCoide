#include <stdio.h>
using namespace std;
double s, x;
int main()
{
    scanf("%lf%lf", &s, &x);
    double p = 0;
    double v = 7;
    bool in = false;
    while(p <= s + x)
    {
        if(p >= s - x)
        {
            if(in)
            {
                printf("y");
                return 0;
            }
            else
            {
                in = true;
            }
        }
        p += v;
        v *= 0.98;
    }
    printf("n");
    return 0;
}
