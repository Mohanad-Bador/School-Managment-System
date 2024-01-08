#include <stdio.h>
#include "student.h"

int main(){
//MAIN_MENU();
    Stack s;
    CreateStack(&s);
    Student student;
    while(1){
        int choice;
        printf("\nMain Menu\nPlease Enter the number of function you want to use\n");
        printf("1. New Student\n");
        printf("2. Delete Student\n");
        printf("3. Print\n");
        printf("4. Student List\n");
        printf("5. Student Edit\n");
        printf("6. Student Score\n");
        printf("7. Rank Students According to Score\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%i", &choice);

        switch(choice) {
            case 1:
                printf("You chose New Student.\n");
                NEW_STUDENT(&student,&s);
                break;
            case 2:
                printf("You chose Delete Student.\n");
                DELETE_STUDENT(&s);
                break;
            case 3:
                printf("You chose Print.\n");
                PRINT_STUDENT(&student,&s);
                break;
            case 4:
                printf("You chose Student List.\n");
                STUDENT_LIST(&s);
                break;
            case 5:
                printf("You chose Student Edit.\n");
                STUDENT_EDIT(&student,&s);
                break;
            case 6:
                printf("You chose Student Score.\n");
                STUDENT_SCORE(&s);
                break;
            case 7:
                printf("You chose Rank Students.\n");
                RANK_STUDENT(&s);
                break;
            case 8:
                printf("Exiting...\n");
                return 0;
                break;
            default:
                printf("Invalid choice.\n");
        }

    }
}
