#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

int main() {
    struct doubly_linked_list_t* dll = dll_create();
    if(!dll) {
        printf("Failed to allocate memory");
        return 8;
    }

    int choice, val, index, err;

    while(251152) {
        printf("co chcesz: ");
        if(scanf("%d", &choice) != 1) {
            printf("Incorrect input");
            dll_clear(dll);
            free(dll);
            return 1;
        }

        switch (choice) {
            case 0:
                dll_clear(dll);
                free(dll);
                return 0;

            case 1:
                printf("podaj: ");
                if(scanf("%d", &val) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                if(dll_push_back(dll, val) == 2) {
                    printf("Failed to allocate memory");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;

            case 2:
                val = dll_pop_back(dll, &err);
                if(err == 0) {
                    printf("%d\n", val);
                } else {
                    printf("List is empty\n");
                }
                break;

            case 3:
                printf("podaj ");
                if(scanf("%d", &val) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                if(dll_push_front(dll, val) == 2) {
                    printf("Failed to allocate memory");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;

            case 4:
                val = dll_pop_front(dll, &err);
                if(err == 0) {
                    printf("%d\n", val);
                } else {
                    printf("List is empty\n");
                }
                break;

            case 5:
                printf("podaj wart: ");
                if(scanf("%d", &val) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                printf("podaj id: ");
                if(scanf("%d", &index) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                err = dll_insert(dll, index, val);
                if (err == 1) {
                    printf("Index out of range\n");
                } else if (err == 2) {
                    printf("Failed to allocate memory");
                    dll_clear(dll);
                    free(dll);
                    return 8;
                }
                break;

            case 6:
                if(dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }
                printf("podaj index:");
                if(scanf("%d", &index) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                val = dll_remove(dll, index, &err);
                if(err == 0) {
                    printf("%d\n", val);
                } else {
                    printf("Index out of range\n");
                }
                break;

            case 7:
                val = dll_back(dll, &err);
                if(err == 0) {
                    printf("%d\n", val);
                } else {
                    printf("List is empty\n");
                }
                break;

            case 8:
                val = dll_front(dll, &err);
                if(err == 0) {
                    printf("%d\n", val);
                } else {
                    printf("List is empty\n");
                }
                break;
            case 9:
                printf("%d\n", dll_is_empty(dll));
                break;
            case 10:
                if(dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                } else printf("%d\n", dll_size(dll));
                break;
            case 11:
                if(dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }
                dll_clear(dll);
                break;

            case 12:
                if(dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                }
                printf("podaj ");
                if(scanf("%d", &index) != 1) {
                    printf("Incorrect input");
                    dll_clear(dll);
                    free(dll);
                    return 1;
                }
                val = dll_at(dll, index, &err);
                if(err == 0) {
                    printf("%d\n", val);
                } else {
                    printf("Index out of range\n");
                }
                break;

            case 13:
                if(dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                } else dll_display(dll);
                break;
            case 14:
                if(dll_is_empty(dll)) {
                    printf("List is empty\n");
                    break;
                } else dll_display_reverse(dll);
                break;

            default:
                printf("Incorrect input data\n");
        }
    }

    return 0;
}
