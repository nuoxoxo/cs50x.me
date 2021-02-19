#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// test char
// char c = 'a';
// printf("%c", c+1); // output: b

int main(int argc, string argv[])
{
    // check non-neg int
    // check counter
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // check digit in argv[1]
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    int k = atoi(argv[1]);

    // check positivity, prompt input
    if (k <= 0)
    {
        printf("Usage: ./caesar key \n### the key should be a non-negative integer\n");
        return 1;
    }
    else if (k > 0)
    {
        string s = get_string("plaintext: ");

        // modulo k
        if (k > 26)
        {
            k %= 26;
        }
        else
        {
            ;
        }
        
        // wraping using isupper with 97 and 65

        printf("ciphertext: ");

        for (int i = 0; i < strlen(s); i++)
        {
            if (isalpha(s[i]))
            {
                // lower or upper
                if (isupper(s[i]))
                {
                    if (s[i] + k > 90)
                    {
                        printf("%c", s[i] + k - 26); // strangely either 25 & 25 works
                    }
                    else 
                    {
                        printf("%c", s[i] + k);
                    }
                } 
                else
                {
                    if (s[i] + k > 122)
                    {
                        printf("%c", s[i] + k - 26); // 25 !works
                    }
                    else 
                    {
                        printf("%c", s[i] + k);
                    }
                }
            }
            else
            {
                printf("%c", s[i]);
            }
        }

        printf("\n");

    }

    return 0;

}