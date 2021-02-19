#include <string.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    string str = get_string("tell me a story: ");

    int len = strlen(str);
    int num_lt = 0; // count letters
    int num_wd = 1; // words: no space before first word
    int num_st = 0; // count senteces
    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            num_lt += 1;
        }
        else if (isspace(str[i]))
        {
            num_wd += 1;
        }
        else if (ispunct(str[i]))
        {
            if ((str[i]) == '.')
            {
                num_st += 1;
            }
            else if ((str[i]) == '!')
            {
                num_st += 1;
            }
            else if ((str[i]) == '?')
            {
                num_st += 1;
            }
        }
    }
    // calc avg letters and sentences
    float avg_lt = (float)num_lt / (float)num_wd * 100;
    float avg_st = (float)num_st / (float)num_wd * 100;

    // transform into coleman-liau grade
    int c_l = round(0.0588 * avg_lt - 0.296 * avg_st - 15.8);

    // result
    if (c_l > 16)
    {
        printf("Grade 16+\n");
    }
    else if (c_l < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", c_l);
    }
}