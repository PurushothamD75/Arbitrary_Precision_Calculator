#include "main.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR) {
    // If any number is zero, the result is zero
    if ((*head1 == NULL && *tail1 == NULL) || (*head2 == NULL && *tail2 == NULL)) {
        dl_insert_first(headR, tailR, 0);
        return SUCCESS;
    }

    // Detect negativity
    int is_negative = 0;
    if (((*head1)->data < 0 && (*head2)->data >= 0) || ((*head1)->data >= 0 && (*head2)->data < 0)) {
        is_negative = 1;
    }

    // Remove any negative signs for multiplication logic (handled at the end)
    if ((*head1)->data < 0) (*head1)->data *= -1;
    if ((*head2)->data < 0) (*head2)->data *= -1;

    // Temporary pointers for traversal
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    // Result linked list initialization
    *headR = *tailR = NULL;

    // Position trackers
    int position = 0;

    while (temp2) {
        int carry = 0;
        int multiplier = temp2->data;

        // Partial result for each digit of temp2
        Dlist *partial_result = NULL, *partial_tail = NULL;

        // Add zeros to match the position (shifting in multiplication)
        for (int i = 0; i < position; i++) {
            dl_insert_first(&partial_result, &partial_tail, 0);
        }

        temp1 = *tail1; // Reset temp1 for the next digit in temp2
        while (temp1) {
            int product = (temp1->data * multiplier) + carry;
            carry = product / 10;         // Carry for the next digit
            int digit = product % 10;    // Current digit

            dl_insert_first(&partial_result, &partial_tail, digit); // Use insert_first
            temp1 = temp1->prev;
        }

        // If there's a carry left, add it to the result
        if (carry) {
            dl_insert_first(&partial_result, &partial_tail, carry); // Use insert_first
        }

        // Add the partial result to the main result
        addition(headR, tailR, &partial_result, &partial_tail, headR, tailR);

        temp2 = temp2->prev;
        position++; // Increment position for the next digit in temp2
    }

    // Restore the sign for the result
    if (is_negative && *headR) {
        (*headR)->data *= -1;
    }

    return SUCCESS;
}
