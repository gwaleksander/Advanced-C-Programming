#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STRUCT_SIZE 24

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename);
int decode_message(const struct message_t *cp, int size, char *msg, int text_size);

int main()
{
    struct message_t strukt[1000];
    const char str[1101];
    char nazwa[31];

    printf("podaj:");
    scanf("%30s", nazwa);

    switch (load_data(strukt, 1000, nazwa))
    {
    case -2:
        printf("Couldn't open file");
        return 4;
    case -3:
        printf("File corrupted");
        return 6;
    default:
        if (decode_message((const struct message_t *)strukt, 1000, (char *)str, sizeof(str)) != 1)
        {
            printf("%s", str);
        }
        return 0;
    }
}

int load_data(struct message_t *cp, int size, const char *filename)
{
    if (filename == NULL || cp == NULL || size <= 0)
    {
        return -1;
    }

    FILE *plik = fopen(filename, "rb");
    if (plik == NULL)
    {
        return -2;
    }

    unsigned int n = 0;

    if (fread(&n, sizeof(unsigned int), 1, plik) != 1 || n % STRUCT_SIZE != 0)
    {
        fclose(plik);
        return -3;
    }

    n /= STRUCT_SIZE;

    if (n > (unsigned int)size)
        n = size;
    else
        size = (int)n;

    while (n > 0 && fread(cp, STRUCT_SIZE, 1, plik) == 1)
    {
        n--;
        cp++;
    }

    if (feof(plik) != 0)
    {
        fclose(plik);
        return -3;
    }

    fclose(plik);
    return size;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size)
{
    if (size <= 0 || size > 1000 || msg == NULL || cp == NULL || text_size <= 0)
    {
        return 1;
    }

    int i = 0, curr = 0;
    unsigned char *cpPtr = (unsigned char *)cp;

    while (isalpha(*cpPtr) == 0 && isdigit(*cpPtr) == 0)
    {
        cpPtr++;
    }

    while (251152)
    {
        if (i == size)
        {
            *msg = '\x0';
            break;
        }

        i++;
        cpPtr++;

        if (curr + 7 >= text_size - 1)
        {
            memmove(msg, cpPtr, text_size - curr - 1);
            msg += text_size - curr - 1;
            *msg = '\x0';
            break;
        }

        memmove(msg, cpPtr, 7);
        curr += 7;
        msg += 7;
        cpPtr += 19;

        if (curr + 4 >= text_size)
        {
            memmove(msg, cpPtr, text_size - curr - 1);
            msg += text_size - curr - 1;
            *msg = '\x0';
            break;
        }

        memmove(msg, cpPtr, 4);
        curr += 4;

        if (curr >= text_size)
        {
            *msg = '\x0';
            break;
        }

        msg += 4;
        cpPtr += 4;

        if (*(cpPtr - 1) == '\x0' || *cpPtr == '\x0')
        {
            *msg = '\x0';
            break;
        }
    }
    return 0;
}