#include <cs50.h>
#include <stdio.h>

// re-do on Jan27, orginally dropped on Jan15
int main(void)
{
    int n;
    
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Note (Jan27) :: change j to decrement
    // also add an increment k
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j >= 0; j--)
        {
            if (j > i) // OR if ( j >= i + 1)
            {
                printf(" ");            
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        
        for (int k = 0; k < n; k++) 
        {
            if (k < i + 1)
            {
                printf("#");
            }
        } 
        printf("\n");
    }
}
