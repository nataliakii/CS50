#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool is_alpha(string text, int len);
bool duplicate_check(string text);
string subst(string a, string text);

int main(int argc, string argv[])
{
    printf("argc %i\n", argc);
    printf("argv1 %s\n", argv[1]);

    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string plaintext;
    int len = strlen(argv[1]);
    bool chars = is_alpha(argv[1], len);
    bool no_duplicates = duplicate_check(argv[1]);

    if (chars && no_duplicates && len == 26 && argc == 2)
    {
        plaintext = get_string("Plaintext:");
        string to_return = subst(argv[1], plaintext);
        printf("ciphertext: %s\n", to_return);
        return 0;
    }

    else if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else
    {
        return 1;
    }
}

string subst(string a, string text)
{
    int len = strlen(text);
    string to_return = malloc(len + 1);

    for (int i = 0; i < len; i++)
    {
        char letter = text[i];
        if (isupper(letter) && isalpha(letter))
        {
            int index = letter - 'A';
            letter = toupper(a[index]);

        }
        else if (islower(letter) && isalpha(letter))
        {
            int index = letter - 'a';
            if (isupper(a[index]))
            {
                letter = tolower(a[index]);
                letter = a[index];
            }
        }
        to_return[i] = letter;
    }
    return to_return;
}

bool is_alpha(const string text, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(text[i]))
        {
            return false;
        }
    }
    return true;
}

bool duplicate_check(string text)
{
    bool seen[26] = {false};

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            int index = tolower(text[i]) - 'a';

            if (seen[index])
            {
                return false; // Duplicate character found
            }

            seen[index] = true;
        }
    }

    printf("No duplicates\n");
    return true; // No duplicate characters found
}