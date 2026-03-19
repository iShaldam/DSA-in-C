/* Group 2 - Passengers on a Train
	In your team of 2-3 persons, review, discuss and implement the following problem specification for a chosen domain.
   Part B: Queue Operations
*/

#include "quizQueue2.h"

int main(void) {

  Queue q = {NULL, NULL}; /* initialize empty queue */

  unsigned int choice;
  char inputBuf[10];

  queueInstructions();
  printf("? ");
  fgets(inputBuf, sizeof(inputBuf), stdin);
  choice = (unsigned int)strtoul(inputBuf, NULL, 10);

  while (choice != 7) {
    switch (choice) {
    case 1:
      if (!isQueueEmpty(&q)) {
        frontOfQueue(&q);
      } else {
        puts("Queue is empty. No passengers in line.");
      }
      break;
    case 2:
      if (!isQueueEmpty(&q)) {
        backOfQueue(&q);
      } else {
        puts("Queue is empty. No passengers in line.");
      }
      break;
    case 3: {
      char id[20];
      char ticketBuf[20];
      char genderBuf[5];
      float ticket;
      char gender;

      printf("Enter Passenger ID: ");
      while (1) {
        if (!fgets(id, sizeof(id), stdin)) {
          printf("Input error. Enter Passenger ID: ");
          continue;
        }
        id[strcspn(id, "\n")] = '\0';
        if (strlen(id) == 0) {
          printf("Passenger ID cannot be empty. Enter Passenger ID: ");
          continue;
        }
        break;
      }

      printf("Enter Ticket Price: ");
      while (1) {
        if (!fgets(ticketBuf, sizeof(ticketBuf), stdin)) {
          printf("Input error. Enter Ticket Price: ");
          continue;
        }
        char *endptr;
        ticket = strtof(ticketBuf, &endptr);
        if (endptr == ticketBuf || (*endptr != '\n' && *endptr != '\0')) {
          printf("Invalid input. Enter a valid Ticket Price: ");
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
        genderBuf[strcspn(genderBuf, "\n")] = '\0';
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

      enqueue(&q, id, ticket, gender);
      printQueue(&q);
      break;
    }
    case 4:
      if (!isQueueEmpty(&q)) {
        dequeue(&q);
      } else {
        puts("Queue is empty. No passengers to board.");
      }
      printQueue(&q);
      break;
    case 5:
      printQueue(&q);
      break;
    case 6: {
    	char searchKey[20];

        printf("Enter search-key (Passenger ID): ");
        while (1) {
        if (!fgets(searchKey, sizeof(searchKey), stdin)) {
        printf("Input error. Enter search-key (Passenger ID): ");
        continue;
    	}
        searchKey[strcspn(searchKey, "\n")] = '\0';   /* remove newline */
        if (strlen(searchKey) == 0) {
        printf("Search key cannot be empty. Enter search-key (Passenger ID): ");
        continue;
    	}
        break;
    }
        searchQueue(&q, searchKey);
        break;
    }    	
    default:
      printf("Invalid choice.\n");
      break;
    }
    queueInstructions();
    printf("? ");
    fgets(inputBuf, sizeof(inputBuf), stdin);
    choice = (unsigned int)strtoul(inputBuf, NULL, 10);
  }

  printf("Exiting Application...\n");
}