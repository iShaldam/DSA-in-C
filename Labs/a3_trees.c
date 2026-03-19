#include "a3_trees.h"

int main (void) {
	
	TreeNodePtr rootPtr = NULL;
	
	unsigned int choice;
    char inputBuf[10];              /* buffer for reading menu choice via fgets */

    instructions();
    printf("? ");
    fgets(inputBuf, sizeof(inputBuf), stdin);
    choice = (unsigned int)strtoul(inputBuf, NULL, 10);
    
    while (choice != 7){
    	switch (choice) {
    		case 1: { // board passengers
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
                    if (searchNode(rootPtr, id) != NULL) {
                        printf("Passenger ID %s already exists. Enter a different Passenger ID: ", id);
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
                    if (isDuplicateTicket(rootPtr, ticket)) {
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

                insertNode(&rootPtr, id, ticket, gender);    /* add passenger to tree */
                inOrder(rootPtr);
                break;
            }
    		case 2: { // exit passenger
                char id[20];
                printf("Enter Passenger ID to exit: ");
                while (1) {
                    if (!fgets(id, sizeof(id), stdin)) {
                        printf("Input error. Enter Passenger ID to exit: ");
                        continue;
                    }
                    if (id[strlen(id) - 1] == '\n')
                        id[strlen(id) - 1] = '\0';          /* remove newline left by fgets */
                    if (strlen(id) == 0) {
                        printf("Passenger ID cannot be empty. Enter Passenger ID to exit: ");
                        continue;
                    }
                    break;
                }

                deleteNode(&rootPtr, id);
                inOrder(rootPtr); // show updated list
                break;
            }
    		case 3: { // find passenger
                char id[20];
                printf("Enter Passenger ID to find: ");
                while (1) {
                    if (!fgets(id, sizeof(id), stdin)) {
                        printf("Input error. Enter Passenger ID to find: ");
                        continue;
                    }
                    if (id[strlen(id) - 1] == '\n')
                        id[strlen(id) - 1] = '\0';          /* remove newline left by fgets */
                    if (strlen(id) == 0) {
                        printf("Passenger ID cannot be empty. Enter Passenger ID to find: ");
                        continue;
                    }
                    break;
                }

                TreeNodePtr foundPtr = searchNode(rootPtr, id);
                if (foundPtr != NULL) {
                    printf("Passenger details: Passenger ID: %s, Ticket Number: %u, Gender: %c\n",
                           foundPtr->passengerId, foundPtr->ticketNumber, foundPtr->passengerGender);
                } else {
                    printf("No passenger found with ID %s.\n", id);
                }
                break;
            }
    		case 4: // pre-order
    			preOrder(rootPtr);
    			break;
    		case 5: // post-order
    			postOrder(rootPtr);
    			break;
    		case 6: // in-order
    			inOrder(rootPtr);
    			break;
    		default:
    			printf("Invalid option.\n\n");
    			break;
    		} // end switch
    		
    	instructions();
        printf("? ");
        fgets(inputBuf, sizeof(inputBuf), stdin);
        choice = (unsigned int)strtoul(inputBuf, NULL, 10);
        
    } // end while
    
    	printf("Exiting Application...\n");	
    	
} // end main
