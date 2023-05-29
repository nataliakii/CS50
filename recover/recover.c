#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    // Open memory card
    FILE *infile = fopen(argv[1], "r");

    if (infile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    int fileCount = 0;
    FILE *img = NULL;
    uint8_t buffer[512];

    // Repeat until the end of the card
    while (fread(buffer, sizeof(uint8_t), 512, infile) == 512)
    {
        // Look for the beginning of a JPEG: 0xff 0xd8 0xff and the 4th byte is 0xe0, 0xe1, ..., 0xef
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // Close the previous JPEG file
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new JPEG file
            char filename[8];
            sprintf(filename, "%03i.jpg", fileCount);
            img = fopen(filename, "w");
            fileCount++;
        }

        // Write the buffer to the current JPEG file
        if (img != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), 512, img);
        }
    }

    // Close any remaining files
    if (img != NULL)
    {
        fclose(img);
    }

    // Close the input file
    fclose(infile);

    return 0;
}