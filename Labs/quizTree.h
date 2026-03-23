#ifndef QUIZTREE_H
#define QUIZTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE  1

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
void        insertNode(TreeNodePtr *treePtr, const char *id, unsigned int ticket, char gender);
TreeNodePtr binaryTreeSearch(TreeNodePtr treePtr, const char *key);
void        searchNode(TreeNodePtr *treePtr, const char *value, TreeNodePtr *parentPtr, TreeNodePtr *tempNodePtr, int *found);
void        deleteNode(TreeNodePtr *treePtr, const char *value);
void        inOrder(TreeNodePtr treePtr);
void        preOrder(TreeNodePtr treePtr);
void        postOrder(TreeNodePtr treePtr);
int         isDuplicateTicketTree(TreeNodePtr treePtr, unsigned int ticket);
int         isTreeEmpty(TreeNodePtr treePtr);
void        treeMenu(void);

/* Function Definitions */

void insertNode(TreeNodePtr *treePtr, const char *id, unsigned int ticket, char gender)
{
   if(*treePtr == NULL){
      *treePtr = (TreeNodePtr)malloc(sizeof(TreeNode));
      if ( *treePtr != NULL) {
        strncpy((*treePtr)->passengerId, id, 19);
         (*treePtr)->passengerId[19] = '\0';
         (*treePtr)->ticketNumber    = ticket;
         (*treePtr)->passengerGender = gender;
         (*treePtr)->leftPtr = NULL;
         (*treePtr)->rightPtr = NULL;
      }
      else {
         printf("Passenger %s not added. No memory available.\n", id);
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

int isTreeEmpty(TreeNodePtr treePtr) {
	return (treePtr == NULL);
}

// Returns 1 if ticket number already exists in the BST, 0 otherwise.
// Note: BST is ordered by passengerId, so we must traverse to find ticket duplicates.
int isDuplicateTicketTree(TreeNodePtr treePtr, unsigned int ticket) {
    if (treePtr == NULL) {
        return 0;
    }
    if (treePtr->ticketNumber == ticket) {
        return 1;
    }
    return isDuplicateTicketTree(treePtr->leftPtr, ticket) ||
           isDuplicateTicketTree(treePtr->rightPtr, ticket);
}

/* search for key in tree */
TreeNodePtr binaryTreeSearch(TreeNodePtr treePtr, const char *key)
{
   if (treePtr == NULL)                                   /* implies treePtr is NULL */
   {
      return NULL;
   }
   else if (strcmp(key, treePtr->passengerId) == 0)      /* implies key == treePtr->passengerId */
   {
      return treePtr;
   }
   else if (strcmp(key, treePtr->passengerId) < 0)       /* implies key < treePtr->passengerId */
   {
      return binaryTreeSearch(treePtr->leftPtr, key);
   }
   else                                                   /* implies key > treePtr->passengerId */
   {
      return binaryTreeSearch(treePtr->rightPtr, key);
   }
}

void searchNode(TreeNodePtr *treePtr, const char *value, TreeNodePtr *parentPtr, TreeNodePtr *tempNodePtr, int *found)
{
   TreeNodePtr tempPtr;
   tempPtr = *treePtr;
   *found = FALSE;
   *parentPtr = NULL;

   while (tempPtr != NULL)
   {
      if (strcmp(tempPtr->passengerId, value) == 0)
      {
         *found = TRUE;
         *tempNodePtr = tempPtr;
         return;
      }

      *parentPtr = tempPtr;
      if (strcmp(tempPtr->passengerId, value) > 0)
         tempPtr = tempPtr->leftPtr;
      else
         tempPtr = tempPtr->rightPtr;
   }
}

/* deletes a node from the binary search tree */
void deleteNode(TreeNodePtr *treePtr, const char *value)
{
   int found;
   TreeNodePtr parentPtr, tempNodePtr, replacementNodePtr;

   /* if tree is empty */
   if (*treePtr == NULL)
   {
      printf("No passengers are currently on the list.\n");
      return;
   }

   parentPtr = NULL;
   tempNodePtr = NULL;

   /* find the node to be deleted */
   searchNode(treePtr, value, &parentPtr, &tempNodePtr, &found);

   /* if the node is not found */
   if (found == FALSE)
   {
      printf("No passenger found with ID %s.\n", value);
      return;
   }

   /* if the node to be deleted has two children */
   if (tempNodePtr->leftPtr != NULL && tempNodePtr->rightPtr != NULL)
   {
      parentPtr = tempNodePtr;
      replacementNodePtr = tempNodePtr->rightPtr;

      while (replacementNodePtr->leftPtr != NULL)
      {
         parentPtr = replacementNodePtr;
         replacementNodePtr = replacementNodePtr->leftPtr;
      }

      strncpy(tempNodePtr->passengerId, replacementNodePtr->passengerId, 19);
      tempNodePtr->passengerId[19] = '\0';
      tempNodePtr->ticketNumber    = replacementNodePtr->ticketNumber;
      tempNodePtr->passengerGender = replacementNodePtr->passengerGender;
      tempNodePtr = replacementNodePtr;
   }

   /* if the node to be deleted has no child */
   if (tempNodePtr->leftPtr == NULL && tempNodePtr->rightPtr == NULL)
   {
      if (parentPtr == NULL)
         *treePtr = NULL;
      else if (parentPtr->rightPtr == tempNodePtr)
         parentPtr->rightPtr = NULL;
      else
         parentPtr->leftPtr = NULL;

      free(tempNodePtr);
      return;
   }

   /* if the node to be deleted has only rightPtr */
   if (tempNodePtr->leftPtr == NULL && tempNodePtr->rightPtr != NULL)
   {
      if (parentPtr == NULL)
         *treePtr = tempNodePtr->rightPtr;
      else if (parentPtr->leftPtr == tempNodePtr)
         parentPtr->leftPtr = tempNodePtr->rightPtr;
      else
         parentPtr->rightPtr = tempNodePtr->rightPtr;

      free(tempNodePtr);
      return;
   }

   /* if the node to be deleted has only left child */
   if (tempNodePtr->leftPtr != NULL && tempNodePtr->rightPtr == NULL)
   {
      if (parentPtr == NULL)
         *treePtr = tempNodePtr->leftPtr;
      else if (parentPtr->leftPtr == tempNodePtr)
         parentPtr->leftPtr = tempNodePtr->leftPtr;
      else
         parentPtr->rightPtr = tempNodePtr->leftPtr;

      free(tempNodePtr);
      return;
   }
}

/* Print menu */
void treeInstructions(void) {
   printf("Enter choice:\n");
   printf("1) Board passenger\n");
   printf("2) Exit passenger\n");
   printf("3) Find passenger\n");
   printf("4) View all passengers - starting from front of train\n");
   printf("5) View all passengers - starting from back of train\n");
   printf("6) View all passengers - sorted A to Z by ID\n");
   printf("7) Return to main menu\n");
} // end menu

#endif /* QUIZTREE_H */
