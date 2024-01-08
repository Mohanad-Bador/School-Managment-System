#include "student.h"
#include<stdio.h>


///////////////////////////////////////////////////////////
/////////////Stack Implementation//////////////////////////
///////////////////////////////////////////////////////////

void CreateStack (Stack *ptrS){
	ptrS->top=NULL;
}

StackNode *MakeStackNode(Student item){
	StackNode *ptrN;

	ptrN=(StackNode *)malloc(sizeof(StackNode));//save memory location with size of StackNode and cast it to StackNode pointer
	ptrN->entry=item;
	ptrN->next=NULL;
	return ptrN;
}

void Push(Student item, Stack *ptrS){
	StackNode *ptrN=MakeStackNode(item);
	ptrN->next=ptrS->top;
	ptrS->top=ptrN;
}

void Pop(Student *pitem, Stack *ptrS){
	StackNode *ptrN;
	*pitem=ptrS->top->entry;
	ptrN=ptrS->top;
	ptrS->top=ptrS->top->next;
	free(ptrN);
}

int StackEmpty(Stack *ptrS){
	return ptrS->top==NULL;
}

int StackFull(Stack *ptrS){
	return 0;
}

void StackTop(Student *pitem, Stack *ptrS){
	*pitem=ptrS->top->entry;
}

int	StackSize(Stack *ptrS){
  int x;
  StackNode *ptrs=ptrS->top;
  for(x=0; ptrs; ptrs=ptrs->next)
    x++;
  return x;
}

void ClearStack(Stack *ptrS){
	StackNode *ptrN=ptrS->top;
	while(ptrN){
		ptrN=ptrN->next;
		free(ptrS->top);
		ptrS->top=ptrN;
	}
}

StackNode *GetStack(Stack *ptrS, int id) {
    StackNode *ptrN = ptrS->top;

    while (ptrN != NULL) {
        if (ptrN->entry.ID == id) {
            return ptrN;
        }
        ptrN = ptrN->next;
    }
    printf("Student with ID %i not found.\n", id);
    return NULL;
}

void RemoveFromStack(Stack *ptrS, int id) {
    StackNode *ptrN = ptrS->top;
    StackNode *prev = NULL;

    while (ptrN != NULL) {
        if (ptrN->entry.ID == id) {
            if (prev == NULL) {
                ptrS->top = ptrN->next; // Update the top pointer to skip the removed node.
            } else {
                prev->next = ptrN->next;// Update the previous node's next pointer to skip the removed node.
            }

            free(ptrN);
            printf("Student with ID %i has been removed.\n", id);
            return; // Exit the function after removing the student
        }
        prev = ptrN;   // Move the previous pointer to the current node.
        ptrN = ptrN->next;  // Move to the next node.
    }

    printf("Student with ID %i not found.\n", id);
}

void SortAndCopyStack(Stack *srcStack, Stack *destStack) {
    int swapped;
    StackNode *srcNode;
    StackNode *last = NULL;

    if (StackEmpty(srcStack)) {
        return;
    }

    // Copy the original stack to the destination stack
    for (srcNode = srcStack->top; srcNode != NULL; srcNode = srcNode->next) {
        Push(srcNode->entry, destStack);
    }

    // Bubble sort the destination stack by student names
    do {
        swapped = 0;
        StackNode *destNode = destStack->top;

        while (destNode->next != last) {
            if (strcmp(destNode->entry.Name, destNode->next->entry.Name) > 0) {
                Student temp = destNode->entry;
                destNode->entry = destNode->next->entry;
                destNode->next->entry = temp;
                swapped = 1;
            }
            destNode = destNode->next;
        }
        last = destNode;
    } while (swapped);
}

void SortStackBySubjectGrade(Stack *ptrS, int subject) {
    int swapped;
    StackNode *srcNode;
    StackNode *last = NULL;

    if (ptrS->top == NULL) {
        return;
    }
    //Bubble sort by the grade
    do {
        swapped = 0;
        StackNode *destNode = ptrS->top;

        while (destNode->next != last) {
            int comparisonResult = 0;

            switch (subject) {
                case 1:
                    comparisonResult = destNode->next->entry.English_grade - destNode->entry.English_grade;
                    break;
                case 2:
                    comparisonResult = destNode->next->entry.Math_grade - destNode->entry.Math_grade;
                    break;
                case 3:
                    comparisonResult = destNode->next->entry.CS_grade - destNode->entry.CS_grade;
                    break;
                case 4:
                    comparisonResult = destNode->next->entry.Total - destNode->entry.Total;
                    break;
                default:
                    // Handle invalid subject gracefully
                    break;
            }

            if (comparisonResult > 0) {
                Student temp = destNode->entry;
                destNode->entry = destNode->next->entry;
                destNode->next->entry = temp;
                swapped = 1;
            }
            destNode = destNode->next;
        }
        last = destNode;
    } while (swapped);
}

int isValidDate(Date date) {
    //Check for year
    if (date.year < 1900 || date.year > 2023) {
        printf("Invalid Date\n");
        return 0;
    }
    //Check for month
    if (date.month < 1 || date.month > 12) {
        printf("Invalid Date\n");
        return 0; // Month out of range
    }

    int daysInMonth;
    if (date.month == 2) {
        // Check for leap year
        if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    } else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
        daysInMonth = 30;
    } else {
        daysInMonth = 31;
    }

    if (date.day < 1 || date.day > daysInMonth) {
        printf("Invalid Date\n");
        return 0; // Day out of range
    }

    return 1; // Date is valid
}

/////////////////////////////////////////////////////////////////////
/////////////////////////Student Functions///////////////////////////
/////////////////////////////////////////////////////////////////////
static int ID=0;
void NEW_STUDENT(Student *ptrStudent,Stack *ptrS){
    getchar();
    ptrStudent->ID=++ID;// Increment the student ID and assign it to the new student.
    printf("Student ID is: %i\n",ptrStudent->ID);

    printf("Enter Student Name: ");
    fgets(ptrStudent->Name,sizeof(ptrStudent->Name),stdin);
    ptrStudent->Name[strcspn(ptrStudent->Name, "\n")] = '\0';// Remove the newline character.

    do{printf("Enter Date of Birth dd/mm/yyyy : ");
    scanf("%i %i %i"
          ,&ptrStudent->Birthday.day
          ,&ptrStudent->Birthday.month
          ,&ptrStudent->Birthday.year);
          }while(!isValidDate(ptrStudent->Birthday));


    printf("Enter Student Address: ");
    getchar();// Clear the newline character.
    fgets(ptrStudent->address,sizeof(ptrStudent->address),stdin);// Remove the newline character.
    ptrStudent->address[strcspn(ptrStudent->address, "\n")] = '\0';

    printf("Enter Student Phone Number: ");
    fgets(ptrStudent->phone_no,sizeof(ptrStudent->phone_no),stdin);// Remove the newline character.
    ptrStudent->phone_no[strcspn(ptrStudent->phone_no, "\n")] = '\0';

    ptrStudent->CS_grade=NULL;
    ptrStudent->Math_grade=NULL;
    ptrStudent->English_grade=NULL;
    ptrStudent->Total=NULL;

    Push(*ptrStudent,ptrS);
}

void DELETE_STUDENT(Stack *ptrS){
    if (!StackEmpty(ptrS)){ // Check if the stack is not empty.
        printf("Enter ID of Student you want to delete: ");
        int id;
        scanf("%i",&id);
        RemoveFromStack(ptrS,id);
        }
    else printf("There is no students\n");
}

void PRINT_STUDENT(Student *ptrStudent,Stack *ptrS){
    if (!StackEmpty(ptrS)){ // Check if the stack is not empty.
        printf("Enter ID of Student you want to print: ");
        int id;
        scanf("%i",&id);
        ptrStudent=GetStack(ptrS,id);
        if(ptrStudent!=NULL){
            printf("Student Name is: %s\n",ptrStudent->Name);
            printf("Date of birth is: %i/%i/%i\n"
               ,ptrStudent->Birthday.day
               ,ptrStudent->Birthday.month
               ,ptrStudent->Birthday.year);
            printf("Student ID is: %i\n",ptrStudent->ID);
            printf("Student Address is: %s\n",ptrStudent->address);

            printf("English Score is %i/100\n",ptrStudent->English_grade);
            printf("Math Score is %i/100\n",ptrStudent->Math_grade);
            printf("CS Score is %i/100\n",ptrStudent->CS_grade);
            printf("Total Score is %i/300\n",ptrStudent->Total);
        }
    }
    else printf("There is no students\n");
}

void STUDENT_LIST(Stack *ptrS) {
    if (!StackEmpty(ptrS)){ // Check if the stack is not empty.
        // Create a new stack to store sorted students
        Stack newStack;
        CreateStack(&newStack);

        // Sort the source stack and copy to the new stack
        SortAndCopyStack(ptrS,&newStack);

        // Print students in the new sorted stack
        //TraverseStack(&newStack, &PrintStudentInfo);
        StackNode *ptrN = newStack.top;
        printf("+----+----------------------+-----------------+---------------------+-----------------+-----------+----------+--------------------+----------+\n");
        printf("| ID |        Name          |  Date of Birth  |      Address        |   Phone No.     |  English  |   Math   |  Computer Science  |   Total  |\n");
        printf("+----+----------------------+-----------------+---------------------+-----------------+-----------+----------+--------------------+----------+\n");
        while (ptrN != NULL) {
            printf("| %2i | %-20s |    %02i/%02i/%04i   | %-19s |  +2%-11i  |  %02i/100   |  %02i/100  |       %02i/100       |  %02i/300  |\n"
                   ,ptrN->entry.ID
                   ,ptrN->entry.Name
                   ,ptrN->entry.Birthday.day
                   ,ptrN->entry.Birthday.month
                   ,ptrN->entry.Birthday.year
                   ,ptrN->entry.address
                   ,ptrN->entry.phone_no
                   ,ptrN->entry.English_grade
                   ,ptrN->entry.Math_grade
                   ,ptrN->entry.CS_grade
                   ,ptrN->entry.Total);

            ptrN = ptrN->next;
        }

        // Clear the new stack to release memory
        ClearStack(&newStack);
    }
    else printf("There is no students\n");
}

void STUDENT_EDIT(Student *ptrStudent,Stack *ptrS){
    if (!StackEmpty(ptrS)){ // Check if the stack is not empty.
        printf("Enter ID of Student you want to edit his data: ");
        int id;
        scanf("%i",&id);
        ptrStudent=GetStack(ptrS,id);
        if(ptrStudent!=NULL){
            printf("Student ID is: %i\n",ptrStudent->ID);

            //Change Student Name
            printf("Change Student Name: %s --> ",ptrStudent->Name);
            getchar(); //To consume newline
            fgets(ptrStudent->Name,sizeof(ptrStudent->Name),stdin);
            ptrStudent->Name[strcspn(ptrStudent->Name, "\n")] = '\0';

            //Change Birth Date
            do{ printf("Change Date of Birth: %02d/%02d/%04d --> "
                    ,ptrStudent->Birthday.day
                    ,ptrStudent->Birthday.month
                    ,ptrStudent->Birthday.year);
                scanf("%i %i %i"
                    ,&ptrStudent->Birthday.day
                    ,&ptrStudent->Birthday.month
                    ,&ptrStudent->Birthday.year);
              }while(!isValidDate(ptrStudent->Birthday));

            //Change Student Address
            printf("Change Student Address: %s --> ",ptrStudent->address);
            getchar();//To consume newline
            fgets(ptrStudent->address,sizeof(ptrStudent->address),stdin);
            ptrStudent->address[strcspn(ptrStudent->address, "\n")] = '\0';

            //Change Phone Number
            printf("Change Student Phone Number: %s -->",ptrStudent->phone_no);
            getchar();//To consume newline
            fgets(ptrStudent->phone_no,sizeof(ptrStudent->phone_no),stdin);
            ptrStudent->phone_no[strcspn(ptrStudent->phone_no, "\n")] = '\0';
        }
    }
    else printf("There is no students\n");
}

void STUDENT_SCORE(Stack *ptrS){
    //initialize stack node pointer
    if (!StackEmpty(ptrS)){ // Check if the stack is not empty.
        StackNode *ptrN = ptrS->top;
        while(ptrN!=NULL){
            printf("\nEnter Score of Student ID: %i Name: %s\n",ptrN->entry.ID,ptrN->entry.Name);
            //Do While loop to check if the input is valid
            do {
                printf("Enter a valid English score (0-100): ");
                scanf("%i", &ptrN->entry.English_grade);
            } while (ptrN->entry.English_grade < 0 || ptrN->entry.English_grade > 100);
            do {
                printf("Enter a valid Math score (0-100): ");
                scanf("%i", &ptrN->entry.Math_grade);
            } while (ptrN->entry.Math_grade < 0 || ptrN->entry.Math_grade > 100);
            do {
                printf("Enter a valid CS score (0-100): ");
                scanf("%i", &ptrN->entry.CS_grade);
            } while (ptrN->entry.CS_grade < 0 || ptrN->entry.CS_grade > 100);
            //Total = English score + Math Score + CS  Score
            ptrN->entry.Total=ptrN->entry.English_grade+ptrN->entry.Math_grade+ptrN->entry.CS_grade;

            ptrN=ptrN->next;
        }
    }
    else printf("There is no students\n");
}

void RANK_STUDENT(Stack *ptrS){
    if(!StackEmpty(ptrS)){ // Check if the stack is not empty.
        int choice;
        printf("Enter value you want to sort according to \n1.English\n2.Math\n3.CS\n4.Total\n");
        printf("Enter your choice: ");
        scanf("%i", &choice);
        SortStackBySubjectGrade(ptrS,choice);

        StackNode *ptrN= ptrS->top;
        printf("+----+----------------------+-----------------+---------------------+-----------------+-----------+----------+--------------------+----------+\n");
        printf("| ID |        Name          |  Date of Birth  |      Address        |   Phone No.     |  English  |   Math   |  Computer Science  |   Total  |\n");
        printf("+----+----------------------+-----------------+---------------------+-----------------+-----------+----------+--------------------+----------+\n");
        for(int i=0 ; i<3 ; i++){
            printf("| %2i | %-20s |    %02i/%02i/%04i   | %-19s |  +2%-11i  |  %02i/100   |  %02i/100  |       %02i/100       |  %02i/300  |\n"
                   ,ptrN->entry.ID
                   ,ptrN->entry.Name
                   ,ptrN->entry.Birthday.day
                   ,ptrN->entry.Birthday.month
                   ,ptrN->entry.Birthday.year
                   ,ptrN->entry.address
                   ,ptrN->entry.phone_no
                   ,ptrN->entry.English_grade
                   ,ptrN->entry.Math_grade
                   ,ptrN->entry.CS_grade
                   ,ptrN->entry.Total);

            ptrN = ptrN->next;
        }
    }else printf("There is no students\n");
}

