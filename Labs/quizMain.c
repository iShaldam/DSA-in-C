#include "quizStack.c"
#include "quizQueue.c"
#include "quizTree.c"

int main(void) {
    unsigned int choice;
    char inputBuf[10];

    while (1) {
        printf("\nPASSENGERS ON A TRAIN\n");
        printf("Enter choice:\n");
        printf("1) Stack -- last boarded, first to exit\n");
        printf("2) Queue -- first boarded, first to exit\n");
        printf("3) Tree  -- search passengers by ID\n");
        printf("4) Exit station\n");
        printf("? ");
        fgets(inputBuf, sizeof(inputBuf), stdin);
        choice = (unsigned int)strtoul(inputBuf, NULL, 10);

        switch (choice) {
            case 1: stackMenu(); break;
            case 2: queueMenu(); break;
            case 3: treeMenu();  break;
            case 4:
                printf("Goodbye. Doors are closing.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}
