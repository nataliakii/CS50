#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int count_index(int s, int l);
int *count(string text);

int main(void)
{
    // Prompt the user for some text
    string input = get_string("Text:  ");

    // Count the number of letters, words, and sentences in the text
    int *countArray = count(input);
    int words = countArray[0];
    int letters = countArray[1];
    int sentences = countArray[2];
    int l = (100 * letters) / words;
    int s = (100 * sentences) / words;

    // Compute the Coleman-Liau index
    int currentIndex = count_index(s, l);
    printf("Index is %i\n", currentIndex);

    // Print the grade level
    if (currentIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (currentIndex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", currentIndex);
    }
}

int count_index(int s, int l)
{
    float index = 0.0588 * l - 0.296 * s - 15.8;
    printf("Index is %f\n", index);
    return (int) round(index);
}

int *count(string text)
{
    int spaces = 0;
    int letters = 0;
    int sentences = 0;
    char apostrophe = '\'';

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            spaces++;
            // Check for multiple spaces in a row
            while (isspace(text[i + 1]))
            {
                i++;
            }
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }

        if (isalpha(text[i]))
        {
            letters++;
        }

        if (text[i] == apostrophe && text[i + 1] == 'v')
        {
            spaces++;
        }
    }

    int *countArray = malloc(3 * sizeof(int));
    countArray[0] = spaces + 1;
    countArray[1] = letters;
    countArray[2] = sentences;
    printf("Words: %i, letters: %i, sentences : %i\n", spaces, letters, sentences);

    return countArray;
}
