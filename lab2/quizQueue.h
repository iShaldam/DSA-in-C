#ifndef QUIZQUEUE_H
#define QUIZQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue node: stores passenger data and points to next
struct queueNode {
    char         passengerId[20];      // passenger ID (unique alpha-numeric)
    unsigned int ticketNumber;         // ticket number (numeric)
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
void enqueue(Queue *q, const char *id, unsigned int ticket, char gender);
void dequeue(Queue *q);
int  isQueueEmpty(const Queue *q);
void frontOfQueue(const Queue *q);
void backOfQueue(const Queue *q);
void printQueue(const Queue *q);
void queueInstructions(void);

// Add node to back of queue
void enqueue(Queue *q, const char *id, unsigned int ticket, char gender) {
    // Reject duplicate passenger IDs
    QueueNodePtr scanPtr = q->frontPtr;
    while (scanPtr != NULL) {
        if (strcmp(scanPtr->passengerId, id) == 0) {
            printf("Passenger ID %s already exists. Duplicate IDs are not allowed.\n", id);
            return;
        }
        scanPtr = scanPtr->nextPtr;
    }

    QueueNodePtr newPtr = (QueueNodePtr)malloc(sizeof(QueueNode));

    if (newPtr != NULL) {
        strncpy(newPtr->passengerId, id, 19);
        newPtr->passengerId[19] = '\0';
        newPtr->ticketNumber    = ticket;
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
        printf("Passenger %s not enqueued. No memory available.\n", id);
    }
}

// Remove node from front of queue
void dequeue(Queue *q) {
    QueueNodePtr tempPtr = q->frontPtr;

    printf("Passenger %s (Ticket #%u, Gender: %c) has boarded the train. Doors closing!\n",
           tempPtr->passengerId, tempPtr->ticketNumber, tempPtr->passengerGender);

    q->frontPtr = q->frontPtr->nextPtr;

    if (q->frontPtr == NULL) {
        q->backPtr = NULL;              // queue is now empty
    }

    free(tempPtr);
}

// Return 1 if queue is empty, 0 otherwise
int isQueueEmpty(const Queue *q) {
    return (q->frontPtr == NULL);
}

// Show data at front of queue (next to board)
void frontOfQueue(const Queue *q) {
    printf("Next to board --> Passenger %s (Ticket #%u, Gender: %c) is at the front of the line.\n",
           q->frontPtr->passengerId, q->frontPtr->ticketNumber, q->frontPtr->passengerGender);
}

// Show data at back of queue (last in line)
void backOfQueue(const Queue *q) {
    printf("Last in line --> Passenger %s (Ticket #%u, Gender: %c) is at the back of the queue.\n",
           q->backPtr->passengerId, q->backPtr->ticketNumber, q->backPtr->passengerGender);
}

// Print all nodes from front to back
void printQueue(const Queue *q) {
    QueueNodePtr currentPtr = q->frontPtr;

    if (currentPtr == NULL) {
        puts("No passengers in queue... nothing to print");
    } else {
        printf("-- Boarding Line (front --> back) --\n");
        int position = 1;
        while (currentPtr != NULL) {
            printf("%d. Passenger %s | Ticket #%u | Gender: %c\n",
                   position++, currentPtr->passengerId, currentPtr->ticketNumber, currentPtr->passengerGender);
            currentPtr = currentPtr->nextPtr;
        }
        printf("\n");
    }
}

// Print queue menu
void queueInstructions(void) {
    printf("\nQUEUE OPERATIONS\n");
    printf("Enter choice:\n");
    printf("1) View next passenger to board (front of queue)\n");
    printf("2) View last passenger in line (back of queue)\n");
    printf("3) Passenger joins the boarding line (enqueue)\n");
    printf("4) Passenger boards the train (dequeue)\n");
    printf("5) View all passengers waiting in line\n");
    printf("6) Exit Queue operations\n");
}

#endif /* QUIZQUEUE_H */
