#include "main.h"
#include <stdio.h>
#include <stdlib.h>
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR) {
    if (*head2 == NULL || (*head2)->data == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return FAILURE;
    }

    int is_negative = 0;

    // Handle negative numbers
    if ((*head1)->data == -1) {
        is_negative = !is_negative;
        *head1 = (*head1)->next;
    }
    if ((*head2)->data == -1) {
        is_negative = !is_negative;
        *head2 = (*head2)->next;
    }

    int cmp = compare_numbers(*head1, *head2);

    // If dividend < divisor, quotient is 0
    if (cmp < 0) {
        dl_insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    // If dividend == divisor, quotient is 1
    if (cmp == 0) {
        dl_insert_first(headR, tailR, 1);
        if (is_negative) {
            (*headR)->data *= -1;
        }
        return SUCCESS;
    }

    // Initialize quotient list
    Dlist *quotient_head = NULL, *quotient_tail = NULL;
    Dlist *remainder_head = NULL, *remainder_tail = NULL;
    Dlist *temp = *head1;

    int has_nonzero_digit = 0;  // Track if quotient has nonzero digits

    // Perform long division
    while (temp) {
        dl_insert_last(&remainder_head, &remainder_tail, temp->data);

        int q = 0;
        while (compare_numbers(remainder_head, *head2) >= 0) {
            subtraction(&remainder_head, &remainder_tail, head2, tail2, &remainder_head, &remainder_tail);
            q++;
        }

        if (q > 9) {  // Ensure we store single digits correctly
            int digits[10];
            int index = 0;
            while (q > 0) {
                digits[index++] = q % 10;
                q /= 10;
            }
            for (int i = index - 1; i >= 0; i--) {
                dl_insert_last(&quotient_head, &quotient_tail, digits[i]);
                has_nonzero_digit = 1;
            }
        } else if (q != 0 || has_nonzero_digit) {
            dl_insert_last(&quotient_head, &quotient_tail, q);
            has_nonzero_digit = 1;
        }

        temp = temp->next;
    }

    // If quotient is empty, insert 0
    if (!has_nonzero_digit) {
        dl_insert_first(&quotient_head, &quotient_tail, 0);
    }

    // Assign result
    *headR = quotient_head;
    *tailR = quotient_tail;

    // Apply negative sign if needed
    if (is_negative) {
        dl_insert_first(headR, tailR, -1);
    }

    return SUCCESS;
}


