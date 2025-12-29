#include "comparators.h"

int comp_int(const void *ptr1, const void *ptr2)
{
    if (ptr1 == NULL && ptr2 != NULL)
        return -1;
    if (ptr1 != NULL && ptr2 == NULL)
        return 1;
    if (ptr1 == NULL && ptr2 == NULL)
        return 0;

    const int *v1 = (const int *)ptr1;
    const int *v2 = (const int *)ptr2;

    if (*v1 > *v2)
        return 1;
    else if (*v1 < *v2)
        return -1;

    return 0;
}
int comp_double(const void *ptr1, const void *ptr2)
{
    if (ptr1 == NULL && ptr2 != NULL)
        return -1;
    if (ptr1 != NULL && ptr2 == NULL)
        return 1;
    if (ptr1 == NULL && ptr2 == NULL)
        return 0;

    const double *v1 = (const double *)ptr1;
    const double *v2 = (const double *)ptr2;

    if (*v1 > *v2)
        return 1;
    else if (*v1 < *v2)
        return -1;

    return 0;
}

int comp_point(const void *ptr1, const void *ptr2)
{
    if (ptr1 == NULL && ptr2 != NULL)
        return -1;
    if (ptr1 != NULL && ptr2 == NULL)
        return 1;
    if (ptr1 == NULL && ptr2 == NULL)
        return 0;

    const struct point_t *point1 = (const struct point_t *)ptr1;
    const struct point_t *point2 = (const struct point_t *)ptr2;

    if (point1->x > point2->x)
        return 1;
    else if (point1->x < point2->x)
        return -1;
    else
    {
        if (point1->y > point2->y)
            return 1;
        else if (point1->y < point2->y)
            return -1;

        return 0;
    }
}

int sort(void *tab, int n, size_t size, int (*cmp)(const void *, const void *))
{
    if (tab == NULL || n <= 0 || size == 0 || cmp == NULL)
        return 1;

    char *arr = (char *)tab;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (cmp(arr + j * size, arr + (j + 1) * size) > 0)
            {
                char *temp = malloc(size);
                if (temp == NULL)
                {
                    return 2;
                }

                memcpy(temp, arr + j * size, size);
                memcpy(arr + j * size, arr + (j + 1) * size, size);
                memcpy(arr + (j + 1) * size, temp, size);

                free(temp);
            }
        }
    }

    return 0;
}
