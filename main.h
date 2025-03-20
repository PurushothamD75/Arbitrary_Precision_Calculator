#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
;

typedef struct node {
    struct node *prev;
    int data;
    struct node *next;
} Dlist;

// Function prototypes for the doubly linked list operations
int dl_insert_first(Dlist **head,Dlist **tail, int data);
int dl_insert_last(Dlist **head, Dlist **tail, int data);
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR);
void print_list(Dlist *head);
int compare_numbers(Dlist *head1, Dlist *head2);

#endif
