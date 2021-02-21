#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    long num;

    do
    {
        num = get_long("Number: ");
    }
    while (num < 0); // min valid num of digits is 13

    int x = 0;

    // wrong if int
    long m = num; // for finding x
    long n = num; // for checksum
    int mod1, mod2;
    int sum1 = 0;
    int sum2 = 0;
    // int checksum = sum1 + sum2;

    while (m) // m >= 0
    {
        m /= 10;
        x++;
    }

    if (x != 13 && x != 15 && x != 16)
    {
        printf("INVALID\n");

    }
    else
    {
        int i = 0;
        while (n != 0)
        {
            mod1 = n % 10;
            sum1 += mod1;
            n /= 10;

            mod2 = n % 10;

            if (mod2 * 2 > 9)
            {
                sum2 += mod2 * 2 / 10 + mod2 * 2 % 10 ;
                n /= 10;
            }
            else
            {
                sum2 += (mod2 * 2);
                n /= 10;

            }

        }

        int checksum = sum1 + sum2;

        //  TEST
        //  printf("sum1 %d\n", sum1); printf("sum2 %d\n", sum2); printf("checksum %d x %d \n", checksum, x);

        // checksum
        if (checksum % 10 == 0)
        {
            if (x == 15)
            {
                if (num / 10000000000000 == 37 || num / 10000000000000 == 34) // why pow(10, 15) not working
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");

                }

            }
            else if (x == 13)
            {
                if (num / 1000000000000 == 4)
                {
                    printf("VISA\n");

                }
                else
                {
                    printf("INVALID\n");

                }
            }
            else if (x == 16)
            {
                if (num / 1000000000000000 == 4)
                {
                    printf("VISA\n");
                }
                else if (num / 100000000000000 == 51
                         || num / 100000000000000 == 52
                         || num / 100000000000000 == 53
                         || num / 100000000000000 == 54
                         || num / 100000000000000 == 55)
                {
                    printf("MASTERCARD\n");

                }
                else
                {
                    printf("INVALID\n");

                }

            }
            else
            {
                printf("INVALID\n");
            }

        }
        else
        {
            printf("INVALID\n"); // expect eof if wo
        }

    }

}