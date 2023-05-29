#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>

int collatz(int n)
{

    while (n != 1)
    {
        if (n % 2 == 0)
        {
            return 1+collatz(n /= 2);
        }
        else
        {
            return 1+ collatz(3 * n + 1);
        }
    }
};