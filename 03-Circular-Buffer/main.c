#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "circular_buffer.h"

int main() {
    struct circular_buffer_t *bufor = NULL;
    int capacity, value, err_code;

    printf("podaj pojemnosc: ");
    if (scanf("%d", &capacity) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if(capacity <= 0){
        printf("Incorrect input data");
        return 2;
    }

    int r = circular_buffer_create_struct(&bufor, capacity);
    if (r != 0) {
        printf("Failed to allocate memory");
        return 8;
    }

    int choice = 0, r2 = 0;
    do {
        printf("podaj decyzje: ");

        if (scanf("%d", &choice) != 1) {
            circular_buffer_destroy_struct(&bufor);
            printf("Incorrect input");
            return 1;
        }

        switch (choice) {
            case 0:
                break;
            case 1:
                printf("poidaj wartosc: ");
                if (scanf("%d", &value) != 1) {
                    printf("incorrect input");
                    circular_buffer_destroy_struct(&bufor);
                    return 1;
                }
                circular_buffer_push_back(bufor, value);
                break;
            case 2:
                value = circular_buffer_pop_back(bufor, &err_code);
                if (err_code == 2)  printf("Buffer is empty\n");
                else    printf("%d\n", value);
                break;
            case 3:
                value = circular_buffer_pop_front(bufor, &err_code);
                if (err_code == 2)  printf("Buffer is empty\n");
                else    printf("%d\n", value);
                break;
            case 4:
                if (circular_buffer_empty(bufor))   printf("Buffer is empty");
                else    circular_buffer_display(bufor);
                printf("\n");
                break;
            case 5:
                r2 = circular_buffer_empty(bufor);
                if (r2 == 1)
                    printf("1\n");
                else if (r2 == 0)
                    printf("0\n");
                break;
            case 6:
                r2 = circular_buffer_full(bufor);
                if (r2 == 1)
                    printf("1\n");
                else if (r2 == 0)
                    printf("0\n");
                break;
            default:
                printf("Incorrect input data\n");
                break;
        }
    } while (choice != 0);

    circular_buffer_destroy_struct(&bufor);

    return 0;
}