#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int current_number_of_elements = 0;

int circular_buffer_create(struct circular_buffer_t *a, int N){
    if(a == NULL || N <= 0) return 1;
    a->ptr = (int*)malloc(N * sizeof(int));
    if(a->ptr == NULL)  return 2;
    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;
    return 0;
}
int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){
    if(cb == NULL || N <= 0)    return 1;
    *cb = (struct circular_buffer_t*)malloc(sizeof(struct circular_buffer_t));
    if (*cb == NULL)    return 2;
    if(circular_buffer_create(*cb, N) != 0){
        free(*cb);
        return 2;
    }
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL) return;

    free(a->ptr);
    a->ptr = NULL;
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a == NULL || *a == NULL) return;

    if ((*a)->ptr != NULL) {
        circular_buffer_destroy((*a));
    }

    free(*a);
    *a = NULL;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
    if(cb == NULL || cb->ptr == NULL)  return 1;
    if(cb->end < 0 || cb->begin < 0 || cb->capacity <= 0 || cb->end > cb->capacity || cb->begin > cb->capacity)   return 1;

    *(cb->ptr + cb->end) = value;
    cb->end = (cb->end + 1) % cb->capacity;

    if (cb->end == cb->begin && !cb->full) {
        cb->full = 1;
    }

    if (cb->full && cb->begin != cb->end) {
        cb->begin = (cb->begin + 1) % cb->capacity;
    }

    if(current_number_of_elements < cb->capacity)   current_number_of_elements++;

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity) {
        if (err_code != NULL)   *err_code = 1;
        return -251152;
    }

    if (a->begin == a->end && !a->full) {
        if (err_code != NULL)   *err_code = 2;
        return -251152;
    }

    int return_value = *(a->ptr + a->begin);
    a->begin = (a->begin + 1) % a->capacity;

    if (err_code != NULL)   *err_code = 0;
    a->full = 0;
    current_number_of_elements--;

    return return_value;
}
int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code){
    if(a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity)   { if(err_code != NULL) *err_code = 1; return -251152; }
    if(a->begin == a->end && !a->full)  { if(err_code != NULL) *err_code = 2; return -251152; }

    a->end = (a->end + a->capacity - 1) % a->capacity;
    int return_value = *(a->ptr + a->end );
    a->full = 0;

    if(err_code != NULL) *err_code = 0;
    current_number_of_elements--;

    return return_value;
}

int circular_buffer_empty(const struct circular_buffer_t *a){
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity)    return -1;
    if (a->begin == a->end && !a->full || current_number_of_elements == 0) return 1;
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *cb) {
    if (cb == NULL || cb->ptr == NULL || cb->end < 0 || cb->begin < 0 || cb->capacity <= 0 || cb->end > cb->capacity || cb->begin > cb->capacity)    return -1;
    if (cb->full || current_number_of_elements == cb->capacity)   return 1;
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a){
    if (a == NULL || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity)    return;
    if (circular_buffer_empty(a))   return;

    int current = a->begin;
    do {
        printf("%d ", *(a->ptr + current));
        current = (current + 1) % a->capacity;
    } while (current != a->end);
}