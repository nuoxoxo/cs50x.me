#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check count
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check key length
    if (strlen(argv[1]) != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check for non alpha and duplicate char
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }

            argv[1][i] = toupper(argv[1][i]); // dangerous step yet seems supposed to be

            if (argv[1][i] == argv[1][j])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    string s = get_string("plaintext: ");

    printf("ciphertext: ");

    // char c;

    // note that key is touppered
    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = 0; j < strlen(argv[1]); j++)
        {

            if (isupper(s[i]))
            {
                // the two numeric values are 65 ascii char apart
                if (s[i] == j + 65)
                {
                    printf("%c", argv[1][j]);
                }
                else
                {
                    ;
                }
            }
            else if (islower(s[i]))
            {
                // c = ;
                if (toupper(s[i]) == j + 65)
                {
                    printf("%c", tolower(argv[1][j]));
                }
            }
            else
            {
                printf("%c", s[i]);

                // print gibberish if no break
                break;
            }
        }
    }
    printf("\n");
}
