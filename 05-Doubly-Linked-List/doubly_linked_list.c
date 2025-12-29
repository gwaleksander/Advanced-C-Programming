//
// Created by Olek on 26.05.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

struct doubly_linked_list_t* dll_create(){
    struct doubly_linked_list_t *dll = malloc(sizeof(struct doubly_linked_list_t));
    if(!dll) {
        return NULL;
    }
    dll->head = NULL;
    dll->tail = NULL;
    return dll;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value) {
    if(!dll)    return 1;

    struct node_t *node = malloc(sizeof(struct node_t));
    if(!node)    return 2;

    node->data = value;
    node->next = NULL;
    node->prev = dll->tail;
    if (dll->tail) {
        dll->tail->next = node;
    } else {
        dll->head = node;
    }
    dll->tail = node;

    return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value) {
    if(!dll) return 1;

    struct node_t* new_node = malloc(sizeof(struct node_t));
    if(!new_node) return 2;

    new_node->data = value;
    new_node->next = dll->head;
    new_node->prev = NULL;
    if(dll->head) {
        dll->head->prev = new_node;
    } else {
        dll->tail = new_node;
    }
    dll->head = new_node;

    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code) {
    if(!dll || !dll->head) {
        if(err_code)    *err_code = 1;
        return -1;
    }

    struct node_t* tmp = dll->head;
    int val = dll->head->data;

    dll->head = dll->head->next;
    if(dll->head) {
        dll->head->prev = NULL;
    } else {
        dll->tail = NULL;
    }
    free(tmp);

    if(err_code) *err_code = 0;
    return val;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code) {
    if(!dll || dll->tail == NULL) {
        if (err_code) *err_code = 1;
        return -1;
    }
    struct node_t* tmp = dll->tail;
    int val = dll->tail->data;

    dll->tail = dll->tail->prev;

    if(dll->tail) {
        dll->tail->next = NULL;
    } else {
        dll->head = NULL;
    }
    free(tmp);

    if(err_code) *err_code = 0;
    return val;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code) {
    if(!dll || dll->head == NULL) {
        if(err_code) *err_code = 1;
        return -1;
    }
    if(err_code) *err_code = 0;
    return dll->head->data;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code) {
    if(!dll || dll->tail == NULL) {
        if(err_code) *err_code = 1;
        return -1;
    }
    if(err_code) *err_code = 0;
    return dll->tail->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll) {
    if(!dll) return NULL;
    return dll->head;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll) {
    if(!dll) return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll) {
    if(!dll) return -1;
    int size = 0;
    struct node_t* curr = dll->head;
    while(curr) {
        size++;
        curr = curr->next;
    }
    return size;
}

int dll_is_empty(const struct doubly_linked_list_t* dll) {
    if(!dll) return -1;
    if(dll->head)   return 0;
    return 1;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if(!dll || !dll->head || !dll->tail) {
        if(err_code) *err_code = 1;
        return -1;
    }

    struct node_t* cur = dll->head;
    for (unsigned i = 0; i < index; i++) {
        if (cur == NULL) {
            if(err_code) *err_code = 1;
            return -1;
        }
        cur = cur->next;
    }

    if (cur == NULL) {
        if(err_code) *err_code = 1;
        return -1;
    }

    if(err_code) *err_code = 0;
    return cur->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value) {
    if(!dll) return 1;
    if(index == 0) return dll_push_front(dll, value);

    struct node_t* curr = dll->head;
    for (unsigned i = 0; i < (index - 1); i++) {
        if(curr == NULL) return 1;
        curr = curr->next;
    }

    struct node_t* node = malloc(sizeof(struct node_t));
    if(node == NULL) return 2;
    if(curr == NULL) {
        free(node);
        return 1;
    }
    node->data = value;
    node->next = curr->next;
    node->prev = curr;
    if(curr->next) {
        curr->next->prev = node;
    } else {
        dll->tail = node;
    }
    curr->next = node;

    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if(!dll || !dll->head) {
        if(err_code) *err_code = 1;
        return -1;
    }
    if(index == 0) return dll_pop_front(dll, err_code);

    struct node_t* curr = dll->head;
    for (unsigned i = 0; i < index; i++) {
        if(curr == NULL) {
            if(err_code) *err_code = 1;
            return -1;
        }
        curr = curr->next;
    }

    int val = curr->data;
    if(curr->prev) {
        curr->prev->next = curr->next;
    }
    if(curr->next) {
        curr->next->prev = curr->prev;
    }
    if(curr == dll->tail) {
        dll->tail = curr->prev;
    }

    free(curr);

    if(err_code) *err_code = 0;
    return val;
}

void dll_clear(struct doubly_linked_list_t* dll) {
    if(!dll || !dll->head) return;

    struct node_t* curr = dll->head, *next;
    while(curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll) {
    if(!dll || !dll->head) return;
    struct node_t* curr = dll->head;
    while(curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void dll_display_reverse(const struct doubly_linked_list_t* dll) {
    if(!dll || !dll->tail) return;
    struct node_t* curr = dll->tail;
    while(curr) {
        printf("%d ", curr->data);
        curr = curr->prev;
    }
    printf("\n");
}