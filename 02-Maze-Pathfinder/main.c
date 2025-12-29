#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_maze(const char *filename, char ***labirynth);
int solve_maze(char **maze, int x, int y);
void free_maze(char **maze);

int rows, cols, corrupted = 0;

int main()
{
    char *filename = malloc(31);
    if (filename == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("opodaj:");
    scanf("%30s", filename);

    char **eo;
    int res1 = load_maze(filename, &eo);

    free(filename);
    if (corrupted)
    {
        res1 = 3;
        free_maze(eo);
    }
    switch (res1)
    {
    case 1:
        return 1;
    case 2:
        printf("Couldn't open file");
        return 4;
    case 3:
        printf("File corrupted");
        return 6;
    case 4:
        printf("Failed to allocate memory");
        return 8;
    default:
        break;
    }
    if (solve_maze(eo, -1, -1) == 0)
    {
        printf("Couldn't find path");
        free_maze(eo);
        return 0;
    }
    else
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols - 1; ++j)
            {
                printf("%c", *(*(eo + i) + j));
            }
            printf("\n");
        }
    }

    free_maze(eo);
    return 0;
}

int load_maze(const char *filename, char ***labirynth)
{
    if (filename == NULL || labirynth == NULL)
        return 1;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 2;

    int row_count = 0, row_size = 0, previous_row_size = 0, exit_count = 0, entry_count = 0;
    char *file_line = malloc(200);
    if (file_line == NULL)
    {
        fclose(file);
        return 4;
    }
    while (fgets(file_line, 512, file))
    {
        previous_row_size = row_size;
        row_size = 0;
        while (*(file_line + row_size) != '\n' && *(file_line + row_size) != '\0')
        {
            if (*(file_line + row_size) == 'a')
                entry_count++;
            if (*(file_line + row_size) == 'b')
                exit_count++;
            row_size++;
        }
        if (previous_row_size != row_size && previous_row_size != 0)
        {
            fclose(file);
            free(file_line);
            return 3;
        }
        row_count++;
    }
    free(file_line);
    if (exit_count != 1)
        corrupted = 1;
    if (entry_count != 1)
        corrupted = 1;
    if (row_count == 0)
    {
        fclose(file);
        return 3;
    }
    row_size = previous_row_size + 1;

    char **lab_ptr = calloc(row_count + 1, sizeof(char *));
    if (lab_ptr == NULL)
    {
        fclose(file);
        return 4;
    }
    *(lab_ptr + row_count) = NULL;

    for (int i = 0; i < row_count; ++i)
    {
        *(lab_ptr + i) = malloc(row_size);
        if (*(lab_ptr + i) == NULL)
        {
            for (int j = 0; j < i; ++j)
            {
                free(*(lab_ptr + j));
            }
            free(lab_ptr);
            lab_ptr = NULL;
            fclose(file);
            return 4;
        }
    }

    rewind(file);

    for (int i = 0; i < row_count; ++i)
    {
        for (int j = 0; j < row_size; ++j)
        {
            char chr = fgetc(file);
            if (chr == '\n')
            {
                *(*(lab_ptr + i) + j) = '\0';
                break;
            }
            *(*(lab_ptr + i) + j) = chr;
        }
    }
    fclose(file);

    *(*(lab_ptr + row_count - 1) + row_size - 1) = '\0';

    *labirynth = lab_ptr;

    rows = row_count;
    cols = row_size;

    return 0;
}

int solve_maze(char **maze, int x, int y)
{
    if (maze == NULL)
        return -1;

    if (x >= cols - 1 || y >= rows)
        return -1;

    if (x > 0 && y > 0 && *(*(maze + y) + x) == 'b')
        return 1;

    for (int i = 0; i < rows; ++i)
    {
        if ((int)strlen(*(maze + i)) + 1 != cols)
            return -1;
    }

    if (x == -1 && y == -1)
    {
        for (int i = 0; *(maze + i) != NULL; i++)
        {
            for (int j = 0; *(*(maze + i) + j) != '\0'; j++)
            {
                if (*(*(maze + i) + j) == 'a')
                {
                    x = j;
                    y = i;
                    break;
                }
            }
        }
    }

    if (x < 0 || y < 0)
        return -1;

    if (*(*(maze + y) + x) == ' ' || *(*(maze + y) + x) == 'a')
    {
        if (*(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = '*';

        if (solve_maze(maze, x, y + 1) == 1)
            return 1;
        if (solve_maze(maze, x, y - 1) == 1)
            return 1;
        if (solve_maze(maze, x - 1, y) == 1)
            return 1;
        if (solve_maze(maze, x + 1, y) == 1)
            return 1;

        if (*(*(maze + y) + x) != 'a')
            *(*(maze + y) + x) = ' ';
    }
    else if (*(*(maze + y) + x) == '\0')
        return -1;

    return 0;
}

void free_maze(char **maze)
{
    if (maze == NULL)
        return;
    for (int i = 0; *(maze + i) != NULL; ++i)
    {
        free(*(maze + i));
    }
    free(maze);
    maze = NULL;
}