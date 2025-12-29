#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

union bit_set
{
    unsigned char byte;
};

int encode(const char *input, char *txt, const char *output);
int decode(const char *filename, char *txt, int size);

int main()
{
    char choice;
    char mess[10001], input_file_name[31], output_file_name[31];

    printf("co chcesz zrobic?");
    scanf("%c", &choice);
    while (getchar() != '\n')
        ;
    switch (choice)
    {
    case 'e':
    case 'E':
        printf("podaj tekst: ");
        fgets(mess, 1001, stdin);
        if (strlen(mess) > 1001)
            while (getchar() != '\n')
                ;
        *(mess + strlen(mess) - 1) = '\0';
        printf("podaj input: ");
        scanf("%30s", input_file_name);
        while (getchar() != '\n')
            ;
        printf("podaj output: ");
        scanf("%30s", output_file_name);
        while (getchar() != '\n')
            ;
        int exit_code = encode(input_file_name, mess, output_file_name);
        if (exit_code == 0)
        {
            printf("File saved");
            return 0;
        }
        else if (exit_code == 2)
        {
            printf("Couldn't open file");
            return 4;
        }
        else if (exit_code == 4)
        {
            printf("Couldn't create file");
            return 5;
        }
        else
        {
            printf("File corrupted");
            return 6;
        }
    case 'd':
    case 'D':
        printf("podaj input: ");
        scanf("%30s", input_file_name);
        int eexit_code = decode(input_file_name, mess, 1001);
        if (eexit_code == 0)
        {
            printf("%s", mess);
            return 0;
        }
        else if (eexit_code == 2)
        {
            printf("Couldn't open file");
            return 4;
        }
        else
        {
            printf("File corrupted");
            return 6;
        }
    default:
        printf("Incorrect input data");
        return 1;
    }
}

int encode(const char *input, char *txt, const char *output)
{
    if (input == NULL || txt == NULL || output == NULL)
        return 1;

    FILE *img_input = fopen(input, "r");
    if (img_input == NULL)
    {
        return 2;
    }

    FILE *img_output = fopen(output, "w");
    if (img_output == NULL)
    {
        fclose(img_input);
        return 4;
    }

    int txt_size = 0;
    while (*(txt + txt_size) != '\0')
        txt_size++;

    char c1;
    int input_size = 0, space_count = 0, check2 = 1;
    while ((c1 = fgetc(img_input)) != EOF)
    {
        input_size++;
        if (c1 == ' ' && check2)
        {
            space_count++;
        }
        if (c1 == '\n' && check2)
        {
            check2 = 0;
        }
    }
    rewind(img_input);

    if (input_size / 8 < txt_size)
    {
        fclose(img_input);
        fclose(img_output);
        return 3;
    }

    int it = 0, space_it = 0;

    union bit_set set1, set2;

    while (1)
    {
        if (it < txt_size)
        {
            set1.byte = (unsigned char)*(txt + it);
            unsigned char byte_value = set1.byte;
            int bit, second_bit;
            for (int j = 7; j >= 0; j--)
            {
                bit = (int)(byte_value / pow(2, j));

                fscanf(img_input, "%hhu", &set2.byte);
                space_it++;

                unsigned char second_byte_value = set2.byte;
                second_bit = 0;
                for (int ij = 7; ij >= 0; ij--)
                {
                    second_bit = (int)(second_byte_value / pow(2, ij));
                    second_byte_value %= (int)pow(2, ij);
                }
                if (second_bit == 0 && bit == 1)
                {
                    set2.byte += 1;
                    fprintf(img_output, "%hhu ", set2.byte);
                }
                else if (second_bit == 1 && bit == 0)
                {
                    set2.byte -= 1;
                    fprintf(img_output, "%hhu ", set2.byte);
                }
                else
                {
                    fprintf(img_output, "%hhu ", set2.byte);
                }
                if (space_it == space_count)
                {
                    fputc('\n', img_output);
                    space_it = 0;
                }
                byte_value %= (int)pow(2, j);
            }
            it++;
        }
        else
        {
            if (fscanf(img_input, "%hhu", &set2.byte) == 1)
            {
                space_it++;
                unsigned char second_byte_value = set2.byte;
                int second_bit = 0;
                for (int j = 7; j >= 0; j--)
                {
                    second_bit = (int)(second_byte_value / pow(2, j));
                    second_byte_value %= (int)pow(2, j);
                }
                if (second_bit == 1)
                {
                    set2.byte -= 1;
                }
                fprintf(img_output, "%hhu ", set2.byte);
                if (space_it == space_count)
                {
                    fputc('\n', img_output);
                    space_it = 0;
                }
            }
            else
            {
                if (!isdigit(fgetc(img_input)) && !feof(img_input))
                {
                    fclose(img_input);
                    if (img_output != NULL)
                        fclose(img_output);
                    return 3;
                }
                else
                {
                    if (img_input != NULL)
                        fclose(img_input);
                    if (img_output != NULL)
                        fclose(img_output);
                    break;
                }
            }
        }
    }

    return 0;
}

int decode(const char *filename, char *txt, int size)
{
    if (filename == NULL || txt == NULL || size < 1)
    {
        return 1;
    }

    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
        return 2;

    union bit_set set;
    int character = 0, character_bit_count = 7, bit, it = 0;
    while (fscanf(file, "%hhu", &set.byte) == 1)
    {
        unsigned char byte_value = set.byte;
        bit = 0;
        for (int j = 7; j >= 0; j--)
        {
            bit = (int)(byte_value / pow(2, j));
            byte_value %= (int)pow(2, j);
        }
        if (bit == 1)
            character += (int)pow(2, character_bit_count);
        character_bit_count--;
        if (character_bit_count < 0)
        {
            if (it < size - 1)
            {
                *(txt + it) = (char)character;
                it++;
            }
            character_bit_count = 7;
            character = 0;
        }
    }
    if (!isdigit(fgetc(file)) && !feof(file))
    {
        fclose(file);
        return 3;
    }
    *(txt + it) = '\0';
    fseek(file, -1, SEEK_END);
    if (fgetc(file) != '\n')
    {
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}