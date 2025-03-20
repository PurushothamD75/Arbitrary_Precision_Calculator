#include "main.h"
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int sum = 0, carry = 0;

    // Start from the least significant digits (tails of both lists)
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    // Initialize result list as empty
    *headR = *tailR = NULL;

    // Loop until both numbers are completely processed and no carry is left
    while (temp1 != NULL || temp2 != NULL || carry)
    {
        sum = carry;  // Start with carry from the previous addition
        
        // Add digit from the first number if available
        if (temp1)
        {
            sum += temp1->data;
            temp1 = temp1->prev;
        }
        
        // Add digit from the second number if available
        if (temp2)
        {
            sum += temp2->data;
            temp2 = temp2->prev;
        }

        // Compute new carry for the next iteration
        carry = sum / 10;
        sum = sum % 10;  // Keep only the last digit
        
        // Insert the sum digit at the beginning of the result list
        dl_insert_first(headR, tailR, sum);  
    }

    return SUCCESS;
}
