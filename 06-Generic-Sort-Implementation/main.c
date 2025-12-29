#include <stdio.h>
#include "comparators.h"

int main()
{
    printf("decyzja: ");
    int choice;
    if (scanf("%d", &choice) != 1)
    {
        printf("incorrect input");
        return 1;
    }

    printf("ile elementow: ");
    int num_of_elements = 0;
    if (scanf("%d", &num_of_elements) != 1)
    {
        printf("incorrect input");
        return 1;
    }

    if (num_of_elements <= 0)
    {
        printf("incorrect input data");
        return 2;
    }

    if (choice == 0)
    {
        int *tab = malloc(num_of_elements * sizeof(int));
        if (tab == NULL)
        {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("decyzja:");
        for (int i = 0; i < num_of_elements; ++i)
        {
            if (scanf("%d", (tab + i)) != 1)
            {
                printf("incorrect input");
                free(tab);
                return 1;
            }
        }

        sort(tab, num_of_elements, sizeof(int), comp_int);

        for (int i = 0; i < num_of_elements; ++i)
        {
            printf("%d ", *(tab + i));
        }

        free(tab);
        return 0;
    }
    else if (choice == 1)
    {
        double *tab = malloc(num_of_elements * sizeof(double));
        if (tab == NULL)
        {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("decyzja:");
        for (int i = 0; i < num_of_elements; ++i)
        {
            if (scanf("%lf", (tab + i)) != 1)
            {
                printf("incorrect input");
                free(tab);
                return 1;
            }
        }

        sort(tab, num_of_elements, sizeof(double), comp_double);

        for (int i = 0; i < num_of_elements; ++i)
        {
            printf("%lf ", *(tab + i));
        }

        free(tab);
        return 0;
    }
    else if (choice == 2)
    {
        struct point_t *tab = malloc(num_of_elements * sizeof(struct point_t));
        if (tab == NULL)
        {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("decyzja:");
        for (int i = 0; i < num_of_elements; ++i)
        {
            if (scanf("%lf %lf", &(tab + i)->x, &(tab + i)->y) != 2)
            {
                printf("incorrect input");
                free(tab);
                return 1;
            }
        }

        sort(tab, num_of_elements, sizeof(struct point_t), comp_point);

        for (int i = 0; i < num_of_elements; ++i)
        {
            printf("%lf %lf\n", (tab + i)->x, (tab + i)->y);
        }

        free(tab);
        return 0;
    }
}