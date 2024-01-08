#ifndef SCHOOL_H
#define SCHOOL_H

///////////////////////////////////////////////////////
//////////////////School Header////////////////////////
///////////////////////////////////////////////////////

typedef struct date {
    int day;
    int month;
    int year;
} Date;

typedef struct school_students {
    int ID,CS_grade,Math_grade,English_grade,Total;;
    char Name[50];
    char phone_no[13];
    char address[50];
    Date Birthday;
} Student;

///////////////////////////////////////////////////////////
/////////////Stack Header /////////////////////////////////
///////////////////////////////////////////////////////////

typedef struct stacknode{
	Student entry;
	struct stacknode *next;
}StackNode;

typedef struct stack{
	StackNode *top;
}Stack;

void	CreateStack		(Stack *ptrS);
StackNode *MakeStackNode(Student item);
void	Push			(Student item, Stack *ptrS);
void	Pop				(Student *pitem , Stack *ptrS);
int		StackEmpty		(Stack *ptrS);
int		StackFull		(Stack *ptrS);
void	StackTop		(Student *pitem, Stack *ptrS);
int		StackSize		(Stack *ptrS);
void	ClearStack		(Stack *ptrS);
StackNode *GetStack(Stack *ptrS, int id);
void RemoveFromStack(Stack *ptrS, int id);
void SortAndCopyStack(Stack *srcStack, Stack *destStack);
void SortStackBySubjectGrade(Stack *ptrS, int subject);
int isValidDate(Date date);

void NEW_STUDENT(Student *ptrStudent,Stack *ptrS);
void DELETE_STUDENT(Stack *ptrS);
void PRINT_STUDENT(Student *ptrStudent,Stack *ptrS);
void STUDENT_LIST(Stack *srcStack);
void STUDENT_EDIT(Student *ptrStudent,Stack *ptrS);
void STUDENT_SCORE(Stack *ptrS);
void RANK_STUDENT(Stack *ptrS);


#endif /* SCHOOL_H */
