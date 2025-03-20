#include"main.h"
int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *ptr = malloc(sizeof(Dlist));
    if(ptr == NULL)
    {
        return FAILURE;
    }
    ptr->data = data;
    ptr->prev= NULL;
    ptr -> next = *head;
    if(*head == NULL)
    {
        *tail = ptr;
    }
    else
    {
        (*head)->prev = ptr;
    }
    *head = ptr;
    return SUCCESS;
}

int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *ptr = malloc(sizeof(Dlist));
    if(ptr == NULL)
    return FAILURE;
    ptr->data = data;
    ptr->prev = NULL;
    ptr->next = NULL;
    if(*head == NULL)
    {
        *head = *tail = ptr;
        return SUCCESS;
    }
    (*tail)->next = ptr;
    ptr->prev = *tail;
    *tail = ptr;
    return SUCCESS;
}

void print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    //printf("Head -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		    // if (head)
		    //     printf("");
	    }
    	//printf(" Tail\n");
    }
}

// int compare_numbers(Dlist *head1, Dlist *head2) {
int compare_numbers(Dlist *head1, Dlist *head2) 
{
    int len1 = 0, len2 = 0;
    Dlist *temp1 = head1, *temp2 = head2;

    // Calculate the lengths of both numbers
    while (temp1) 
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2) 
    {
        len2++;
        temp2 = temp2->next;
    }

    // Compare based on length first
    if (len1 > len2) return 1;  // head1 is greater
    if (len1 < len2) return -1; // head2 is greater

    // If lengths are equal, compare digit by digit
    temp1 = head1;
    temp2 = head2;
    while (temp1 && temp2) {
        if (temp1->data > temp2->data) return 1;
        if (temp1->data < temp2->data) return -1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return 0; // Numbers are equal
}