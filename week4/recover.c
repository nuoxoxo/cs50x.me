#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check legal usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n"); 
        return 1;
    }
    
    // create pointer set
    FILE *input = fopen(argv[1], "r");
    FILE *output = NULL;

    // check if file valid
    if (input == NULL)
    {
        printf("Unable to open: %s\n", argv[1]);
        return 1;
    }

    // int and uint8_t wont work
    unsigned char buffer[512];
    // keep track of no. of image
    int counter = 0;
    // check if in the middle of process
    int is_reading = 0;
    
    // while reading dataof sizeof 1 unit (of 512), fread keep returning size of 1
    while (fread(&buffer, 512, 1, input) == 1)
    {
        // if signature found :: two possibilities
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // either is the 1st image -> set is_reading to 1, open new and write
            if (is_reading != 1)
            {
                is_reading = 1;
            }
            // or is the start of new image -> close current file, open new, write new
            else
            {
                fclose(output);
            }

            // to create an EMPTY file, Step 1: need a string to write name in
            char name[8];
            // Step 2: automate the format, involve counter
            sprintf(name, "%03i.jpg", counter);
            // Step 3: use output pointer & fopen to provide memory for name.jpg
            output = fopen(name, "w");
            // update serial filename
            counter++;
        }

        // next job is to write
        if (is_reading == 1)
        {
            fwrite(&buffer, 512, 1, output);
        }
    }

    // remember to close what is NULL
    if (output == NULL)
    {
        fclose(output);
    }
    if (input == NULL)
    {
        fclose(input);
    }

    return 0;
}








