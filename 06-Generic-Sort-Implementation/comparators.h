#ifndef UNTITLED_COMPARATORS_H
#define UNTITLED_COMPARATORS_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

struct point_t
{
    double x;
    double y;
};

int comp_int(const void *ptr1, const void *ptr2);
int comp_double(const void *ptr1, const void *ptr2);
int comp_point(const void *ptr1, const void *ptr2);

int sort(void *tab, int n, size_t size, int (*cmp)(const void *, const void *));

#endif // UNTITLED_COMPARATORS_H
