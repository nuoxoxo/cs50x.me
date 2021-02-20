#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float n;

    do
    {
        n = get_float("Change owed: ");

    }
    while (n < 0);

    // int tt = qt + dm + nk + ct;
    int ct = round(n * 100); // debugged
    int qt = 0;
    int dm = 0;
    int nk = 0;    

    // calculate quarter coins first
    qt = round(ct / 25);
    // use modulo to replace "ct = ct - qt * 25"
    ct = ct % 25;

    if (ct == 0)
    {
        printf("%d\n", qt + dm + nk + ct);
    }
    else
    {
        // calculate dimes
        dm = round(ct / 10);
        ct = ct % 10;

        if (ct == 0)
        {
            printf("%d\n", qt + dm + nk + ct);
        }
        else
        {
            // calculate nickels and pennies
            nk = round(ct / 5);
            ct = ct % 5;

            printf("%d\n", qt + dm + nk + ct);
        }
    }
}
