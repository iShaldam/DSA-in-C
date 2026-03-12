/* Group 2 - Passengers on a Train
	In your team of 2-3 persons, review, discuss and implement the following problem specification for a chosen domain.
*/

// include stack header-file
#include "quizStack.h"

int main(void) {

    StackNodePtr stackPtr = NULL;   /* create stack pointer */

    unsigned int choice;
    char inputBuf[10];              /* buffer for reading menu choice via fgets */

    instructions();
    printf("? ");
    fgets(inputBuf, sizeof(inputBuf), stdin);
    choice = (int)strtol(inputBuf, NULL, 10);

    while (choice != 7) {
        switch (choice) {
            case 1:
                if (!isEmpty(stackPtr)) {
                    topOfStack(stackPtr);   /* print node at the top of the stack */
                } else {
                    puts("There are no passengers on board.");
                }
                break;
            case 2:
                bottomOfStack(stackPtr);   /* print node at the bottom of the stack */
                break;
            case 3: {
                char         id[20];
                char         ticketBuf[20];
                char         genderBuf[5];
                unsigned int ticket;
                char         gender;

                printf("Enter Passenger ID: ");
                while (1) {
                    if (!fgets(id, sizeof(id), stdin)) {
                        printf("Input error. Enter Passenger ID: ");
                        continue;
                    }
                    if (id[strlen(id) - 1] == '\n')
                        id[strlen(id) - 1] = '\0';  /* remove newline left by fgets */
                    if (strlen(id) == 0) {
                        printf("Passenger ID cannot be empty. Enter Passenger ID: ");
                        continue;
                    }
                    if (isDuplicate(stackPtr, id)) {
                        printf("Passenger ID %s already exists. Enter a different ID: ", id);
                        continue;
                    }
                    break;
                }

                printf("Enter Ticket Number: ");
                while (1) {
                    if (!fgets(ticketBuf, sizeof(ticketBuf), stdin)) {
                        printf("Input error. Enter Ticket Number: ");
                        continue;
                    }
                    char *endptr;
                    ticket = (unsigned int)strtoul(ticketBuf, &endptr, 10);
                    if (endptr == ticketBuf || (*endptr != '\n' && *endptr != '\0')) {
                        printf("Invalid input. Enter a valid Ticket Number: ");
                        continue;
                    }
                    if (isDuplicateTicket(stackPtr, ticket)) {
                        printf("Ticket Number %u already exists. Enter a different Ticket Number: ", ticket);
                        continue;
                    }
                    break;
                }

                /* Robust gender input: only accept M or F (case-insensitive), loop until valid */
                while (1) {
                    printf("Enter Gender (M/F): ");
                    if (!fgets(genderBuf, sizeof(genderBuf), stdin)) {
                        printf("Input error.");
                        continue;
                    }

                    // Remove any newline from input
                    if (genderBuf[strlen(genderBuf) - 1] == '\n')
                        genderBuf[strlen(genderBuf) - 1] = '\0';

                    if (genderBuf[0] == 'M' || genderBuf[0] == 'm') {
                        gender = 'M';
                        break;
                    } else if (genderBuf[0] == 'F' || genderBuf[0] == 'f') {
                        gender = 'F';
                        break;
                    } else {
                        printf("Invalid gender. Please enter M or F.\n");
                    }
                }

                stackPtr = push(stackPtr, id, ticket, gender);  /* push node onto stack */
                printStack(stackPtr);                           /* print the stack nodes */
                break;
            }
            case 4:
                if (!isEmpty(stackPtr)) {
                    stackPtr = pop(stackPtr);   /* pop node from stack */
                }
                printStack(stackPtr);           /* print the current stack nodes */
                break;
            case 5:
                printStack(stackPtr);           /* print the stack */
                break;
            case 6: {
                char searchKey[20];

                printf("Enter search-key (Passenger ID): ");
                while (1) {
                    if (!fgets(searchKey, sizeof(searchKey), stdin)) {
                        printf("Input error. Enter search-key (Passenger ID): ");
                        continue;
                    }
                    if (searchKey[strlen(searchKey) - 1] == '\n')
                        searchKey[strlen(searchKey) - 1] = '\0';  /* remove newline */
                    if (strlen(searchKey) == 0) {
                        printf("Search key cannot be empty. Enter search-key (Passenger ID): ");
                        continue;
                    }
                    break;
                }

                searchOfStack(stackPtr, searchKey);           /* search the stack */
                break;
            }
            default:
                printf("Invalid choice.\n\n");
                break;
        }
        instructions();
        printf("? ");
        fgets(inputBuf, sizeof(inputBuf), stdin);
        choice = (int)strtol(inputBuf, NULL, 10);
    }

    printf("End of run.\n");

}