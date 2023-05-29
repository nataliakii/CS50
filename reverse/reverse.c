#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse inputfile outputfile\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inptf = fopen(argv[1], "rb");
    if (inptf == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER head;
    fread(&head, sizeof(WAVHEADER), 1, inptf);

    // Use check_format to ensure WAV format
    int check = check_format(head);
    if (check == 1)
    {
        printf("Input file is not WAV format\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *outptf = fopen(argv[2], "wb");
    if (outptf == NULL)
    {
        printf("Could not open %s.\n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&head, sizeof(WAVHEADER), 1, outptf);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(head);

    // Write reversed audio to file
    // TODO #8
    long buffer[2];
    fseek(inptf, 44, SEEK_END);
    long data_size = ftell(inptf);
    printf("data_size is %li\n", data_size);
    fseek(inptf, 0, SEEK_END);
    long file_size = ftell(inptf);
    printf("File_size is %li\n", file_size);
    fseek(inptf, file_size, SEEK_SET);

    long current_pos = ftell(inptf);
    printf("Current position out of loop is %li\n", current_pos);
    while (current_pos > sizeof(WAVHEADER))
    {
        fseek(inptf, -block_size, SEEK_CUR);
        fread(buffer, block_size, 1, inptf);
        fwrite(buffer, block_size, 1, outptf);
        fseek(inptf, -block_size, SEEK_CUR);
        current_pos = ftell(inptf);
        printf("Current position in a loop is %li\n", current_pos);
        // current_pos -= block_size;
    }

    fclose(inptf);
    fclose(outptf);
    return 0;
}

int check_format(WAVHEADER header)
{
    char expectedFormat[5] = "WAVE";
    char format[5];
    // Copy the format bytes from the header into the format array
    memcpy(format, header.format, 4);
    format[4] = '\0';
    printf("header.format is %s\n", header.format);
    printf("format is %s\n", format);
    printf("expectedformat is %s\n", expectedFormat);

    if (strcmp(expectedFormat, format) == 0)
    {
        printf("Returning 0, WAVE format\n");
        return 0; // WAV format
    }
    else
    {
        printf("NOT WAVE format");
        return 1; // Not WAV format
    }
}

int get_block_size(WAVHEADER header)
{
    int channels = header.numChannels;
    int bytes_per_sample = header.bitsPerSample / 8;
    int block = channels * bytes_per_sample;
    printf("channels nmb is %i\n", channels);
    printf("bytes_per_sample is %i\n", bytes_per_sample);
    printf("block size is %i\n", block);
    return block;
}