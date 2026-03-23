#ifndef QUIZQUEUE_H
#define QUIZQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue node: stores passenger data and points to next
struct queueNode {
    char         passengerId[20];      //passenger ID
    unsigned int ticketNumber;         //ticket number
    char         passengerGender;      //'M' or 'F'
    struct queueNode *nextPtr;         //next node
};

// Shorthand types
typedef struct queueNode  QueueNode;
typedef struct queueNode *QueueNodePtr;

// Function prototypes
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, const char *id, unsigned int ticket, char gender);
void dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
int  isQueueEmpty(QueueNodePtr headPtr);
void front(QueueNodePtr headPtr);
void back(QueueNodePtr tailPtr);
void printQueue(QueueNodePtr headPtr);
void searchQueue(QueueNodePtr headPtr, const char *key);
void queueInstructions(void);
int  isDuplicateQueue(QueueNodePtr headPtr, const char *id);
int  isDuplicateTicketQueue(QueueNodePtr headPtr, unsigned int ticket);
void queueMenu(void);

// Add passenger to the tail of the queue
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, const char *id, unsigned int ticket, char gender) {
    QueueNodePtr newPtr = (QueueNodePtr)malloc(sizeof(QueueNode));

    if (newPtr != NULL) {
        strncpy(newPtr->passengerId, id, 19);
        newPtr->passengerId[19] = '\0';         //null-terminate
        newPtr->ticketNumber    = ticket;
        newPtr->passengerGender = gender;
        newPtr->nextPtr = NULL;

        if (*headPtr == NULL) {                 // queue is empty — insert at head
            *headPtr = newPtr;
        } else {                                //otherwise insert at tail
            (*tailPtr)->nextPtr = newPtr;
        }
        *tailPtr = newPtr;                      //always update tailPtr

        printf("Passenger %s is boarding the train.\n", newPtr->passengerId);
    } else {
        printf("Passenger %s not added. No memory available.\n", id);
    }
}

// Remove passenger from the head of the queue
void dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr) {
    QueueNodePtr tempPtr = *headPtr;

    printf("Passenger ID: %s, Ticket Number: %u, Gender: %c has left the train\n",
           tempPtr->passengerId, tempPtr->ticketNumber, tempPtr->passengerGender);

    *headPtr = (*headPtr)->nextPtr;

    if (*headPtr == NULL) {                     //if queue is now empty, update tailPtr
        *tailPtr = NULL;
    }

    free(tempPtr);
}

// Return 1 if queue is empty, 0 otherwise
int isQueueEmpty(QueueNodePtr headPtr) {
    return (headPtr == NULL);
}

// Show passenger at front of queue
void front(QueueNodePtr headPtr) {
    printf("Passenger ID: %s, Ticket Number: %u, Gender: %c is the first passenger to board.\n",
           headPtr->passengerId, headPtr->ticketNumber, headPtr->passengerGender);
}

// Show passenger at back of queue
void back(QueueNodePtr tailPtr) {
    printf("Passenger ID: %s, Ticket Number: %u, Gender: %c is the last passenger to board.\n",
           tailPtr->passengerId, tailPtr->ticketNumber, tailPtr->passengerGender);
}

// Print all passengers in the queue
void printQueue(QueueNodePtr headPtr) {
    QueueNodePtr currentPtr = headPtr;

    if (currentPtr == NULL) {
        puts("No passengers are currently on board");
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

// Search queue for a passenger by ID
void searchQueue(QueueNodePtr headPtr, const char *key) {
    QueueNodePtr currentPtr = headPtr;
    int position = 0;

    if (currentPtr == NULL) {
        printf("No passengers found on board... nothing to search\n");
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

// Returns 1 if ID already exists in queue, 0 otherwise
int isDuplicateQueue(QueueNodePtr headPtr, const char *id) {
    QueueNodePtr currentPtr = headPtr;

    while (currentPtr != NULL) {
        if (strcmp(currentPtr->passengerId, id) == 0) {
            return 1;   //found a match — duplicate
        }
        currentPtr = currentPtr->nextPtr;
    }
    return 0;   //no match found
}

// Returns 1 if ticket number already exists in queue, 0 otherwise
int isDuplicateTicketQueue(QueueNodePtr headPtr, unsigned int ticket) {
    QueueNodePtr currentPtr = headPtr;

    while (currentPtr != NULL) {
        if (currentPtr->ticketNumber == ticket) {
            return 1;   /* found a match — duplicate! */
        }
        currentPtr = currentPtr->nextPtr;
    }
    return 0;   //no match found
}

// Print menu options
void queueInstructions(void) {
    printf("Enter choice:\n");
    printf("1) Print the passenger at the front of the train\n");
    printf("2) Print the passenger at the back of the train\n");
    printf("3) Board passenger\n");
    printf("4) Exit passenger\n");
    printf("5) Print all passengers on train\n");
    printf("6) Search passengers\n");
    printf("7) Return to main menu\n");
}

#endif //QUIZQUEUE_H
