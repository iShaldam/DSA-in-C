#ifndef QUIZSTACK_H
#define QUIZSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack node: stores passenger data and points to next
struct stackNode {
    char         passengerId[20];      // passenger ID
    unsigned int ticketNumber;         // ticket number
    char         passengerGender;      // 'M' or 'F'
    struct stackNode *nextPtr;         // next node
};

// Shorthand types
typedef struct stackNode  StackNode;
typedef struct stackNode *StackNodePtr;

// Function prototypes
StackNodePtr push(StackNodePtr topPtr, const char *id, unsigned int ticket, char gender);
StackNodePtr pop(StackNodePtr topPtr);
int          isEmpty(StackNodePtr topPtr);
void         topOfStack(StackNodePtr topPtr);
void         bottomOfStack(StackNodePtr topPtr);
void         printStack(StackNodePtr topPtr);
void         searchOfStack(StackNodePtr topPtr, const char *key);
void         instructions(void);

// Add node to top of stack
StackNodePtr push(StackNodePtr topPtr, const char *id, unsigned int ticket, char gender) {
    StackNodePtr newPtr = (StackNodePtr)malloc(sizeof(StackNode));

    if (newPtr != NULL) {
        strncpy(newPtr->passengerId, id, 19);
        newPtr->passengerId[19] = '\0';         // null-terminate
        newPtr->ticketNumber    = ticket;
        newPtr->passengerGender = gender;
        newPtr->nextPtr = topPtr;
        topPtr = newPtr;
        printf("Passenger %s is boarding the train.\n", newPtr->passengerId); // print the passenger being pushed into stack (boarding the train)
    } else {
        printf("Passenger %s not pushed. No memory available.\n", id); // if no memory available
    }

    return topPtr;
}

// Remove node from top of stack
StackNodePtr pop(StackNodePtr topPtr) {
    StackNodePtr tempPtr = topPtr;

    printf("Passenger ID: %s, Ticket Number: %u, Gender: %c has left the train\n",
           tempPtr->passengerId, tempPtr->ticketNumber, tempPtr->passengerGender); // print the passenger being popped (leaving the 'train')

    topPtr = topPtr->nextPtr;
    free(tempPtr);

    return topPtr;
}

// Return 1 if stack is empty, 0 otherwise
int isEmpty(StackNodePtr topPtr) {
    return (topPtr == NULL);
}

// Show data at top of stack
void topOfStack(StackNodePtr topPtr) {
    printf("Passenger ID: %s, Ticket Number: %u, Gender: %c is the last passenger to board.\n",
           topPtr->passengerId, topPtr->ticketNumber, topPtr->passengerGender); // print the passenger at the top-of-stack (last to board)
}

// Show data at bottom of stack
void bottomOfStack(StackNodePtr topPtr) {
    StackNodePtr previousPtr = NULL;
    StackNodePtr currentPtr  = topPtr;

    if (currentPtr == NULL) {
        printf("No passengers found.\n"); // if stack empty
        return;
    }

    while (currentPtr != NULL) {
        previousPtr = currentPtr;
        currentPtr  = currentPtr->nextPtr;
    }

    printf("Passenger ID: %s, Ticket Number: %u, Gender: %c is the first passenger to board\n",
           previousPtr->passengerId, previousPtr->ticketNumber, previousPtr->passengerGender); // print passenger at the bottom-of-stack (first to board)
}

// Print all nodes in stack
void printStack(StackNodePtr topPtr) {
    StackNodePtr currentPtr = topPtr;

    if (currentPtr == NULL) {
        puts("No passengers... nothing to print"); // if stack empty
    } else {
        printf("Passengers on board:\n");
        while (currentPtr != NULL) {
            printf("Passenger ID: %s, Ticket Number: %u, Gender: %c\n",
                   currentPtr->passengerId, currentPtr->ticketNumber, currentPtr->passengerGender);
            currentPtr = currentPtr->nextPtr;
        }
        printf("\n\n");
    }
}

// Search stack for passengerId
void searchOfStack(StackNodePtr topPtr, const char *key) {
    StackNodePtr currentPtr = topPtr;
    int position = 0;

    if (currentPtr == NULL) {
        printf("No passengers found... nothing to search\n"); // if stack is empty
        return;
    }

    while (currentPtr != NULL && strcmp(currentPtr->passengerId, key) != 0) {
        currentPtr = currentPtr->nextPtr;
        position++;
    }

    if (currentPtr == NULL) {
        printf("Passenger %s was not found\n", key);
    } else {
        printf("Passenger ID: %s, Ticket Number: %u, Gender: %c was found at location %d\n",
               currentPtr->passengerId, currentPtr->ticketNumber, currentPtr->passengerGender, position + 1);
    }
}

// Print menu options
void instructions(void) {
    printf("Enter choice:\n");
    printf("1) Print the last to board (top-of-stack)\n");
    printf("2) Print the first to board (bottom-of-stack)\n");
    printf("3) Board passenger (push)\n");
    printf("4) Exit passenger (pop)\n");
    printf("5) Print all passengers on train\n");
    printf("6) Search passengers\n");
    printf("7) Exit Application\n");
}

#endif /* QUIZSTACK_H */
