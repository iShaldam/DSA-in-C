#ifndef QUIZQUEUE_H
#define QUIZQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxPrice 750.0f
#define MinPrice 50.0f

// Queue node: stores passenger data and points to next
struct queueNode {
    char         passengerId[20];      // passenger ID (unique alpha-numeric)
    float 		 ticketPrice;         // the price of the ticket 
    char         passengerGender;      // 'M' or 'F' (character)
    struct queueNode *nextPtr;         // next node
};

// Shorthand types
typedef struct queueNode  QueueNode;
typedef struct queueNode *QueueNodePtr;

// Queue struct holds both ends — avoids global variables
typedef struct {
    QueueNodePtr frontPtr;
    QueueNodePtr backPtr;
} Queue;

// Function prototypes
void enqueue(Queue *q, const char *id, float ticket, char gender);
void dequeue(Queue *q);
int  isQueueEmpty(const Queue *q);
void frontOfQueue(const Queue *q);
void backOfQueue(const Queue *q);
void printQueue(const Queue *q);
void queueInstructions(void);
void searchQueue(const Queue *q, const char *key);


// Add node to back of queue
void enqueue(Queue *q, const char *id, float ticket, char gender) {
    // Reject duplicate passenger IDs
    QueueNodePtr scanPtr = q->frontPtr;
    while (scanPtr != NULL) {
        if (strcmp(scanPtr->passengerId, id) == 0) {
            printf("Passenger ID %s already exists. Duplicate IDs are not allowed.\n", id);
            return;
        }
        scanPtr = scanPtr->nextPtr;
    }
	if (ticket < MinPrice || ticket > MaxPrice) {
		printf("Not a valid price. Ticket must be between $50-750.\n");
		return;
	}
    QueueNodePtr newPtr = (QueueNodePtr)malloc(sizeof(QueueNode));

    if (newPtr != NULL) {
        strncpy(newPtr->passengerId, id, 19);
        newPtr->passengerId[19] = '\0';
        newPtr->ticketPrice    = ticket;
        newPtr->passengerGender = gender;
        newPtr->nextPtr         = NULL;

        if (q->backPtr != NULL) {
            q->backPtr->nextPtr = newPtr;   // link to current back
        } else {
            q->frontPtr = newPtr;           // first node: also the front
        }
        q->backPtr = newPtr;
        printf("Passenger %s has joined the boarding line at the back of the queue.\n", newPtr->passengerId);
    } else {
        printf("Passenger %s is not in line. Train capacity met.\n", id);
    }
} // end enqueue

// Remove node from front of queue
void dequeue(Queue *q) {
    QueueNodePtr tempPtr = q->frontPtr;

    printf("Passenger %s (Ticket $%.2f, Gender: %c) has boarded the train. Doors closing!\n",
           tempPtr->passengerId, tempPtr->ticketPrice, tempPtr->passengerGender);

    q->frontPtr = q->frontPtr->nextPtr;

    if (q->frontPtr == NULL) {
        q->backPtr = NULL;              // queue is now empty
    }

    free(tempPtr);
} // end dequeue

// Return 1 if queue is empty, 0 otherwise
int isQueueEmpty(const Queue *q) {
    return (q->frontPtr == NULL);
} // end isQueueEmpty

// Show data at front of queue (next to board)
void frontOfQueue(const Queue *q) {
    printf("Next to board --> Passenger %s (Ticket $%.2f, Gender: %c) is at the front of the line.\n",
           q->frontPtr->passengerId, q->frontPtr->ticketPrice, q->frontPtr->passengerGender);
} // end frontOfQueue

// Show data at back of queue (last in line)
void backOfQueue(const Queue *q) {
    printf("Last in line --> Passenger %s (Ticket $%.2f, Gender: %c) is at the back of the queue.\n",
           q->backPtr->passengerId, q->backPtr->ticketPrice, q->backPtr->passengerGender);
} // end backOfQueue

// Print all nodes from front to back
void printQueue(const Queue *q) {
    QueueNodePtr currentPtr = q->frontPtr;

    if (currentPtr == NULL) {
        puts("There are no passengers in line.");
    } else {
        printf("-- Boarding Line (front --> back) --\n");
        int position = 1;
        while (currentPtr != NULL) {
            printf("%d. Passenger %s | Ticket $%.2f | Gender: %c\n",
                   position++, currentPtr->passengerId, currentPtr->ticketPrice, currentPtr->passengerGender);
            currentPtr = currentPtr->nextPtr;
        }
        printf("\n");
    }
} // end printQueue

// Print queue menu
void queueInstructions(void) {
    printf("\n--- WELCOME TO XYZ RAIL OPERATIONS ---\n");
    printf("What would you like to do?:\n");
    printf("1) View next passenger to board\n");
    printf("2) View last passenger in line\n");
    printf("3) Passenger joins the boarding line\n");
    printf("4) Passenger boards the train\n");
    printf("5) View all passengers waiting in line\n");
    printf("6) Search for a passenger\n");
    printf("7) Exit Application\n");
} // end menu

void searchQueue(const Queue *q, const char *key){
	QueueNodePtr currentPtr = q->frontPtr; int position = 0;
   
   while(currentPtr != NULL && strcmp(currentPtr->passengerId, key) != 0){
      currentPtr = currentPtr->nextPtr;
      position++;
   }
   if (currentPtr == NULL){ // item not found
      printf("Passenger %d was not found\n", key);
   } 
   else {  // item found
      printf("Passenger ID: %s, Ticket Number: $%.2f, Gender: %c is #%d in line\n",
               currentPtr->passengerId, currentPtr->ticketPrice, currentPtr->passengerGender, position + 1);
   }
} // end searchQueue

#endif /* QUIZQUEUE_H */