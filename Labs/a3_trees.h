#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNode{			/* TreeNode structure definition */
	struct treeNode *leftPtr; 			// left node
 	char         passengerId[20];      //passenger ID
    unsigned int ticketNumber;         //ticket number
    char         passengerGender;      //'M' or 'F'
    struct treeNode *rightPtr;         //right node
};					/* end struct TreeNode */

/* Shorthand types */
typedef struct treeNode   TreeNode;
typedef struct treeNode * TreeNodePtr;

/* Function Prototypes */
void insertNode(TreeNodePtr *treePtr, const char *id, unsigned int ticket, char gender);
//removeNode();
//searchTree();
void inOrder(TreeNodePtr treePtr);
void preOrder(TreeNodePtr treePtr);
void postOrder(TreeNodePtr treePtr);
int isDuplicate(TreeNodePtr treePtr, const char *id);
int isDuplicateTicket(TreeNodePtr treePtr, unsigned int ticket);
int isEmpty(TreeNodePtr treePtr);

/* Function Definitions */

void insertNode(TreeNodePtr *treePtr, const char *id, unsigned int ticket, char gender)
{ 
   if(*treePtr == NULL){	
      *treePtr = malloc(sizeof(TreeNode));
      if ( *treePtr != NULL) { 
        strncpy((*treePtr)->passengerId, id, 19);
         (*treePtr)->passengerId[19] = '\0';
         (*treePtr)->ticketNumber    = ticket;
         (*treePtr)->passengerGender = gender;
         (*treePtr)->leftPtr = NULL;
         (*treePtr)->rightPtr = NULL;
      } 
      else {
         puts("Passenger %s not added. No memory available.\n"); 
      } 
      return; 
   }
   else{ 
      if ( strcmp(id, (*treePtr)->passengerId) < 0 ) { 	/* insert node in left subtree */
         insertNode(&((*treePtr)->leftPtr),id, ticket, gender); 
      } 
      else if (strcmp(id, (*treePtr)->passengerId) > 0) {       /* insert into right subtree*/       
         insertNode(&((*treePtr)->rightPtr),id, ticket, gender);
      } else {
      	printf("Passenger ID %s already exists. Duplicate IDs are not allowed.\n", id);
	  }
  }
} // end insertNode

void inOrder(TreeNodePtr treePtr)
{ 
   /* traverse left subtree, print, traverse right subtree */
   if(treePtr != NULL){
      inOrder(treePtr->leftPtr);
      printf("Passenger ID: %s, Ticket Number: %u, Gender: %c\n",
                   treePtr->passengerId, treePtr->ticketNumber, treePtr->passengerGender);
      inOrder(treePtr->rightPtr);
   }
} // end inOrder

/* traverse the tree preorder */
void preOrder(TreeNodePtr treePtr)
{ 
   /* print, traverse left subtree, traverse right subtree */
   if(treePtr != NULL){
      printf("Passenger ID: %s, Ticket Number: %u, Gender: %c\n",
                   treePtr->passengerId, treePtr->ticketNumber, treePtr->passengerGender);
      preOrder(treePtr->leftPtr);
      preOrder(treePtr->rightPtr);
   }
} // end preOrder

/* traverse the tree postorder */
void postOrder(TreeNodePtr treePtr)
{ 
   /* traverse left subtree, traverse right subtree, print */
   if(treePtr != NULL){
      postOrder(treePtr->leftPtr);
      postOrder(treePtr->rightPtr);
      printf("Passenger ID: %s, Ticket Number: %u, Gender: %c\n",
                   treePtr->passengerId, treePtr->ticketNumber, treePtr->passengerGender);
   }
}  // end postOrder

int isEmpty(TreeNodePtr treePtr) {
	return (treePtr == NULL);
}

// Print menu
void instructions(void) {
    printf("Enter choice:\n");
    printf("1) Board passenger\n");
    printf("2) Exit passenger\n"); // not done
    printf("3) Search passengers\n"); // not done
    printf("4) Show passengers pre-order\n"); // rewrite
    printf("5) Show passengers post-order\n"); // rewrite
    printf("6) Show passengers in-order by ID\n");
    printf("7) Exit Application\n");
} // end menu