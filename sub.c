#include "main.h"
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp1 = *head1, *temp2 = *head2;
    int is_negative = 0;  // Flag to track if the result is negative

    // Move to the end of both lists to determine their lengths
    while (temp1 && temp2)
    {
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // Compare numbers to determine which is larger
    int cmp = compare_numbers(*head1, *head2);
    if (cmp < 0) {
        // If first number is smaller, swap numbers to ensure we subtract smaller from larger
        Dlist *temp_head = *head1, *temp_tail = *tail1;
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = temp_head;
        *tail2 = temp_tail;
        
        is_negative = 1;  // Mark result as negative
    }

    // Reset pointers to the last digits of both numbers
    temp1 = *tail1;
    temp2 = *tail2;
    int borrow = 0, diff;
    
    // Initialize result list as empty
    *headR = *tailR = NULL;

    // Perform digit-by-digit subtraction
    while (temp1 || temp2)
    {
        int digit1 = temp1 ? temp1->data : 0;  // Get current digit of first number
        int digit2 = temp2 ? temp2->data : 0;  // Get current digit of second number

        digit1 = digit1 - borrow;  // Apply previous borrow if any
        
        // Handle borrowing if needed
        if (digit1 < digit2)
        {
            digit1 += 10;  // Borrow from the next digit
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        diff = digit1 - digit2;  // Calculate the difference

        // Insert the result digit at the beginning of the result list
        dl_insert_first(headR, tailR, diff);

        // Move to the previous digits
        if (temp1)
            temp1 = temp1->prev;
        if (temp2)
            temp2 = temp2->prev;
    }

    // Remove leading zeros in the result
    while (*headR && (*headR)->data == 0)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        if (*headR) 
            (*headR)->prev = NULL;
        free(temp);
    }

    // If the result is empty after removing zeros, insert a single zero
    if (!*headR)
    {
        dl_insert_first(headR, tailR, 0);
    }

    // Print negative sign if the result is negative
    if (is_negative)
    {
        printf("-");
    }

    return SUCCESS;
}
