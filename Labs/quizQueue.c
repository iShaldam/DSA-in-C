/* Group 2 - Passengers on a Train
   Lab-Quiz-3: Queue Implementation
*/

#include "quizQueue.h"

void queueMenu(void) {

    QueueNodePtr headPtr = NULL;    /* pointer to front of queue */
    QueueNodePtr tailPtr = NULL;    /* pointer to back of queue */

    unsigned int choice;
    char inputBuf[10];              /* buffer for reading menu choice via fgets */

    queueInstructions();
    printf("? ");
    fgets(inputBuf, sizeof(inputBuf), stdin);
    choice = (unsigned int)strtoul(inputBuf, NULL, 10);

    while (choice != 7) {
        switch (choice) {
            case 1:                                         /* front of queue */
                if (!isQueueEmpty(headPtr)) {
                    front(headPtr);
                } else {
                    puts("No passengers on board.");
                }
                break;

            case 2:                                         /* back of queue */
                if (!isQueueEmpty(headPtr)) {
                    back(tailPtr);
                } else {
                    puts("No passengers on board.");
                }
                break;

            case 3: {                                       /* enqueue */
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
                        id[strlen(id) - 1] = '\0';          /* remove newline left by fgets */
                    if (strlen(id) == 0) {
                        printf("Passenger ID cannot be empty. Enter Passenger ID: ");
                        continue;
                    }
                    if (isDuplicateQueue(headPtr, id)) {
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
                    if (isDuplicateTicketQueue(headPtr, ticket)) {
                        printf("Ticket Number %u already exists. Enter a different Ticket Number: ", ticket);
                        continue;
                    }
                    break;
                }

                while (1) {
                    printf("Enter Gender (M/F): ");
                    if (!fgets(genderBuf, sizeof(genderBuf), stdin)) {
                        printf("Input error.");
                        continue;
                    }
                    if (genderBuf[strlen(genderBuf) - 1] == '\n')
                        genderBuf[strlen(genderBuf) - 1] = '\0'; /* remove newline left by fgets */

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

                enqueue(&headPtr, &tailPtr, id, ticket, gender);    /* add passenger to queue */
                printQueue(headPtr);                                 /* print the queue */
                break;
            }

            case 4:                                         /* dequeue */
                if (!isQueueEmpty(headPtr)) {
                    dequeue(&headPtr, &tailPtr);            /* remove passenger from queue */
                } else {
                    puts("No passengers on board.");
                }
                printQueue(headPtr);                        /* print the current queue */
                break;

            case 5:                                         /* print queue */
                printQueue(headPtr);
                break;

            case 6: {                                       /* search */
                char searchKey[20];

                printf("Enter Passenger ID: ");
                while (1) {
                    if (!fgets(searchKey, sizeof(searchKey), stdin)) {
                        printf("Input error. Enter Passenger ID: ");
                        continue;
                    }
                    if (searchKey[strlen(searchKey) - 1] == '\n')
                        searchKey[strlen(searchKey) - 1] = '\0';  /* remove newline */
                    if (strlen(searchKey) == 0) {
                        printf("Passenger ID cannot be empty. Enter Passenger ID: ");
                        continue;
                    }
                    break;
                }

                searchQueue(headPtr, searchKey);            /* search the queue */
                break;
            }

            default:
                printf("Invalid option.\n\n");
                break;
        }
        queueInstructions();
        printf("? ");
        fgets(inputBuf, sizeof(inputBuf), stdin);
        choice = (unsigned int)strtoul(inputBuf, NULL, 10);
    }

    printf("Returning to main menu...\n");

}
