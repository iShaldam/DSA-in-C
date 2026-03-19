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
TreeNodePtr searchNode(TreeNodePtr treePtr, const char *id);
void deleteNode(TreeNodePtr *treePtr, const char *id);
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

int isEmpty(TreeNodePtr treePtr) {
	return (treePtr == NULL);
}

// Returns 1 if ticket number already exists in the BST, 0 otherwise.
// Note: BST is ordered by passengerId, so we must traverse to find ticket duplicates.
int isDuplicateTicket(TreeNodePtr treePtr, unsigned int ticket) {
    if (treePtr == NULL) {
        return 0;
    }
    if (treePtr->ticketNumber == ticket) {
        return 1;
    }
    return isDuplicateTicket(treePtr->leftPtr, ticket) ||
           isDuplicateTicket(treePtr->rightPtr, ticket);
}

// Search for a passenger by ID in the BST.
TreeNodePtr searchNode(TreeNodePtr treePtr, const char *id)
{
   TreeNodePtr tempPtr = treePtr;
   while (tempPtr != NULL) {
      int cmp = strcmp(id, tempPtr->passengerId);
      if (cmp == 0) {
         return tempPtr;
      }
      if (cmp < 0) {
         tempPtr = tempPtr->leftPtr;
      } else {
         tempPtr = tempPtr->rightPtr;
      }
   }
   return NULL;
}

// Delete a passenger node by ID from the BST.
// Logic is adapted from the week10 delete/search BST approach.
void deleteNode(TreeNodePtr *treePtr, const char *id)
{
   TreeNodePtr parentPtr = NULL;
   TreeNodePtr tempNodePtr = NULL;
   TreeNodePtr currPtr = NULL;

   if (*treePtr == NULL) {
      printf("No passengers are currently on the list.\n");
      return;
   }

   currPtr = *treePtr;
   while (currPtr != NULL) {
      int cmp = strcmp(id, currPtr->passengerId);
      if (cmp == 0) {
         tempNodePtr = currPtr;
         break;
      }
      parentPtr = currPtr;
      if (cmp < 0) {
         currPtr = currPtr->leftPtr;
      } else {
         currPtr = currPtr->rightPtr;
      }
   }

   if (tempNodePtr == NULL) {
      printf("No passenger found with ID %s.\n", id);
      return;
   }

   // If node has two children, replace it with its in-order successor.
   if (tempNodePtr->leftPtr != NULL && tempNodePtr->rightPtr != NULL) {
      TreeNodePtr succParentPtr = tempNodePtr;
      TreeNodePtr replacementNodePtr = tempNodePtr->rightPtr;

      while (replacementNodePtr->leftPtr != NULL) {
         succParentPtr = replacementNodePtr;
         replacementNodePtr = replacementNodePtr->leftPtr;
      }

      // Copy successor data into the node being deleted.
      strncpy(tempNodePtr->passengerId, replacementNodePtr->passengerId, 19);
      tempNodePtr->passengerId[19] = '\0';
      tempNodePtr->ticketNumber = replacementNodePtr->ticketNumber;
      tempNodePtr->passengerGender = replacementNodePtr->passengerGender;

      // Delete the successor node (which has at most one child).
      TreeNodePtr childPtr = replacementNodePtr->rightPtr;
      if (succParentPtr->leftPtr == replacementNodePtr) {
         succParentPtr->leftPtr = childPtr;
      } else {
         succParentPtr->rightPtr = childPtr;
      }
      free(replacementNodePtr);
      return;
   }

   // Node has zero or one child.
   TreeNodePtr childPtr = (tempNodePtr->leftPtr != NULL) ? tempNodePtr->leftPtr : tempNodePtr->rightPtr;
   if (parentPtr == NULL) {
      // Deleting the root node.
      *treePtr = childPtr;
   } else if (parentPtr->leftPtr == tempNodePtr) {
      parentPtr->leftPtr = childPtr;
   } else {
      parentPtr->rightPtr = childPtr;
   }
   free(tempNodePtr);
}

/* Print menu */
void instructions(void) {
   printf("Enter choice:\n");
   printf("1) Board passenger\n");
   printf("2) Exit passenger\n");
   printf("3) Find passenger\n");
   printf("4) View all passengers - starting from front of train\n");
   printf("5) View all passengers - starting from back of train\n");
   printf("6) View all passengers - sorted A to Z by ID\n");
   printf("7) Exit Application\n");
} // end menu
