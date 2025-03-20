/*
Name:PURUSHOTHAM D
Date:05/02/2025
Description:Arbitrary Precision Calculator
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 4) {
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
        return FAILURE;
    }
    
    // Debug statement to print received arguments
    printf("Debug: Received arguments: num1=%s, operator=%s, num2=%s\n", argv[1], argv[2], argv[3]);

    // Define pointers for doubly linked lists to store numbers and result
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    int sign1 = 1, sign2 = 1;  // Default: Both numbers are positive
    int i = 0, j = 0;

    // Handle sign for num1
    if (argv[1][0] == '-') {
        sign1 = -1;  // Mark number as negative
        i = 1;       // Start reading from the next character
    }
    // Convert num1 (string) into a linked list
    for (; argv[1][i] != '\0'; i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            printf("Invalid character in number1: %c\n", argv[1][i]);
            return FAILURE;
        }
        dl_insert_last(&head1, &tail1, argv[1][i] - '0');
    }

    // Handle sign for num2
    if (argv[3][0] == '-') {
        sign2 = -1;  // Mark number as negative
        j = 1;       // Start reading from the next character
    }
    // Convert num2 (string) into a linked list
    for (; argv[3][j] != '\0'; j++) {
        if (argv[3][j] < '0' || argv[3][j] > '9') {
            printf("Invalid character in number2: %c\n", argv[3][j]);
            return FAILURE;
        }
        dl_insert_last(&head2, &tail2, argv[3][j] - '0');
    }

    // Validate operator
    if (strlen(argv[2]) != 1 || (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != '/')) {
        printf("Invalid operator. Supported operators: +, -, x, /\n");
        return FAILURE;
    }
    char operator = argv[2][0];

    // Debug statement to identify the operator
    printf("Debug: Operator identified as '%c'\n", operator);

    int result_sign = 1;  // Default sign of result is positive

    // Perform the appropriate arithmetic operation based on the operator
    switch (operator) {
        case '+':
            if (sign1 == sign2) {
                // If both numbers have the same sign, perform direct addition
                result_sign = sign1;
                if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS) {
                    printf("Addition is successful. Result: ");
                    if (result_sign == -1) printf("-");  // Print negative sign if needed
                    print_list(headR);
                } else {
                    printf("Error in addition\n");
                }
            } else {
                // If signs are different, perform subtraction
                if (compare_numbers(head1, head2) >= 0) {
                    result_sign = sign1;
                    if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS) {
                        printf("Subtraction is successful. Result: ");
                        if (result_sign == -1) printf("-");
                        print_list(headR);
                    } else {
                        printf("Error in subtraction\n");
                    }
                } else {
                    result_sign = sign2;
                    if (subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR) == SUCCESS) {
                        printf("Subtraction is successful. Result: ");
                        if (result_sign == -1) printf("-");
                        print_list(headR);
                    } else {
                        printf("Error in subtraction\n");
                    }
                }
            }
            break;

        case '-':
            if (sign1 != sign2) {
                // If signs are different, add the numbers
                result_sign = sign1;
                if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS) {
                    printf("Addition is successful. Result: ");
                    if (result_sign == -1) printf("-");
                    print_list(headR);
                } else {
                    printf("Error in addition\n");
                }
            } else {
                // If both numbers have the same sign, perform subtraction
                if (compare_numbers(head1, head2) >= 0) {
                    result_sign = sign1;
                    if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS) {
                        printf("Subtraction is successful. Result: ");
                        if (result_sign == -1) printf("-");
                        print_list(headR);
                    } else {
                        printf("Error in subtraction\n");
                    }
                } else {
                    result_sign = -sign1;
                    if (subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR) == SUCCESS) {
                        printf("Subtraction is successful. Result: ");
                        if (result_sign == -1) printf("-");
                        print_list(headR);
                    } else {
                        printf("Error in subtraction\n");
                    }
                }
            }
            break;

        case 'x':
            // Determine the sign of the result (multiplication rule)
            result_sign = sign1 * sign2;
            if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS) {
                printf("Multiplication is successful. Result: ");
                if (result_sign == -1) printf("-");
                print_list(headR);
            } else {
                printf("Error in multiplication\n");
            }
            break;

        case '/':
            // Determine the sign of the result (division rule)
            result_sign = sign1 * sign2;
            if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS) {
                printf("Division is successful. Result: ");
                if (result_sign == -1) printf("-");
                print_list(headR);
            } else {
                printf("Error in division\n");
            }
            break;

        default:
            printf("Invalid operator. Supported operators: +, -, x, /\n");
            return FAILURE;
    }
    
    printf("\n");  // Print newline for better readability
    return SUCCESS;
}
