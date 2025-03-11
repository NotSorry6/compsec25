#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXN 1000
#define ALPHA_LENGTH 26
#define COMMON_LETTERS 10

char* cezar_decipher(char* cipher, int key)
{
    int length = strlen(cipher);
    char* text = (char*) malloc(sizeof(char) * (length + 1));
    for(int i = 0; i < length; i++)
    {
        if(cipher[i] >= 'a' && cipher[i] <= 'z')
        {
            text[i] = (cipher[i] - 'a' - key + 26) % 26 + 'a';
        }
        else if(cipher[i] >= 'A' && cipher[i] <= 'Z')
        {
            text[i] = (cipher[i] - 'A' - key + 26) % 26 + 'A';
        }
        else if(cipher[i] >= '0' && cipher[i] <= '9')
        {
            text[i] = (cipher[i] - '0' - key + 10) % 10 + '0';
        }
        else
        {
            text[i] = cipher[i];
        }
    }
    text[length] = '\0';
    return text;
}

int read_cipher(char* filename, char* cipher)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error opening file.");
        return EXIT_FAILURE;
    }

    if(fgets(cipher, MAXN, fp) == NULL)
    {
        printf("Error reading from file.");
        return EXIT_FAILURE;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int* count_frequencies(char* cipher)
{
    int length = strlen(cipher);
    int* counts = (int*) malloc(sizeof(int) * ALPHA_LENGTH);
    memset(counts, 0, sizeof(int) * ALPHA_LENGTH);
    for(int i = 0; i < length; i++)
    {
        char symbol = tolower(cipher[i]);
        if(symbol >= 'a' && symbol <= 'z')
        {
            int position = symbol - 'a';
            counts[position]++;
        }
    }
    return counts;
}

int get_max_index(int* counts)
{
    int max_index = 0;
    for(int i = 0; i < ALPHA_LENGTH; i++)
    {
        if(counts[i] > counts[max_index])
        {
            max_index = 1;
        }
    }
    return max_index;
}


int main()
{
    char cipher[MAXN];
    read_cipher("cezar.txt",cipher);
    int* frequencies = count_frequencies(cipher);
    char letter = get_max_index(frequencies)+'a';
    char commons[COMMON_LETTERS]={'e', 't', 'a', 'o', 'i', 'n', 's', 'r' ,'h' ,'l' };

    for (int i = 0;i<COMMON_LETTERS;i++)
    {
        int key = abs(letter - commons[i]);
        char* text = cezar_decipher(cipher, key);
        printf("Key = %d -> %s\n", key, text);
        free(text);
    }
    
    return EXIT_SUCCESS;
}
    

