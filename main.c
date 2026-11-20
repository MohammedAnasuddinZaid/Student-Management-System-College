/*
 * ============================================================
 *  STUDENT MANAGEMENT SYSTEM
 *  GRIET - B.Tech First Year - PPS GLOB Mini Project
 * ============================================================
 *
 *  A simple terminal program written in C.
 *  Student details are stored in ordinary arrays while the
 *  program is running. The records are lost when the program
 *  is closed (this is explained in the README).
 *
 *  Only basic C is used:
 *  - variables, arrays and character arrays
 *  - printf(), scanf(), fgets(), getchar()
 *  - if / else, switch, for and while loops
 *  - user-defined functions
 *
 *  No pointers, structures, files, dynamic memory or recursion.
 */

#include <stdio.h>
#include <string.h>

/* ---------- Constants ---------- */
#define MAX_STUDENTS 50   /* maximum number of students */
#define NAME_LENGTH 30    /* maximum characters in a name */
#define SUBJECTS 5        /* number of subjects */

/* ---------- Global arrays ----------
   These are shared by all functions, so we do not need
   pointer parameters anywhere in the program. */
int studentCount = 0;
char names[MAX_STUDENTS][NAME_LENGTH];        /* 50 names, each up to 29 letters */
int rollNumbers[MAX_STUDENTS];                /* 50 roll numbers */
int marks[MAX_STUDENTS][SUBJECTS];            /* 50 students x 5 subjects */
char grades[MAX_STUDENTS][4];                 /* grade text, e.g. "A+" or "F" */

/* ---------- Function declarations (prototypes) ---------- */
void clearInputBuffer(void);
int calculateTotal(int index);
float calculateAverage(int index);
void calculateGrade(int index);
void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void sortStudents(void);

/* ============================================================
   MAIN FUNCTION
   The menu and switch are kept here. All real work is done
   by the small functions below.
   ============================================================ */
int main(void)
{
    int choice;

    while (1)
    {
        printf("\n========================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Sort Students by Total Marks\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        /* Read the menu choice and check that it is a number */
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number from 1 to 5.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                sortStudents();
                break;
            case 5:
                printf("\nThank you for using Student Management System.\n");
                printf("Program exited. Goodbye!\n\n");
                return 0;
            default:
                printf("\nInvalid choice! Please enter a number from 1 to 5.\n");
        }
    }
}

/* ============================================================
   Clears characters left in the input buffer.
   This is needed after scanf() so that fgets() does not read
   the leftover Enter (newline) key.
   ============================================================ */
void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* empty body: we only want to throw the characters away */
    }
}

/* ============================================================
   Adds the marks of one student and returns the total.
   ============================================================ */
int calculateTotal(int index)
{
    int total = 0;
    int i;

    for (i = 0; i < SUBJECTS; i++)
    {
        total = total + marks[index][i];
    }
    return total;
}

/* ============================================================
   Returns the average marks of one student.
   5.0f is used so that the answer is a decimal number.
   ============================================================ */
float calculateAverage(int index)
{
    return calculateTotal(index) / 5.0f;
}

/* ============================================================
   Finds the grade from the average and stores it in the
   global grades array for that student.
   ============================================================ */
void calculateGrade(int index)
{
    float average = calculateAverage(index);

    if (average >= 90)
    {
        strcpy(grades[index], "A+");
    }
    else if (average >= 80)
    {
        strcpy(grades[index], "A");
    }
    else if (average >= 70)
    {
        strcpy(grades[index], "B");
    }
    else if (average >= 60)
    {
        strcpy(grades[index], "C");
    }
    else if (average >= 50)
    {
        strcpy(grades[index], "D");
    }
    else
    {
        strcpy(grades[index], "F");
    }
}

/* ============================================================
   FEATURE 1: ADD STUDENT
   Checks capacity, duplicate roll number and marks range.
   ============================================================ */
void addStudent(void)
{
    int newRoll;
    int i, s, mark;
    int length;

    printf("\n----- ADD STUDENT -----\n");

    /* Check whether the arrays are full */
    if (studentCount >= MAX_STUDENTS)
    {
        printf("Cannot add more students. Maximum capacity (%d) reached.\n",
               MAX_STUDENTS);
        return;
    }

    /* Read and check the roll number */
    printf("Enter roll number: ");
    if (scanf("%d", &newRoll) != 1)
    {
        printf("Invalid roll number. Student not added.\n");
        clearInputBuffer();
        return;
    }

    if (newRoll <= 0)
    {
        printf("Roll number must be a positive number. Student not added.\n");
        clearInputBuffer();
        return;
    }

    /* Linear search for a duplicate roll number */
    for (i = 0; i < studentCount; i++)
    {
        if (rollNumbers[i] == newRoll)
        {
            printf("Roll number %d already exists. Duplicate not allowed.\n",
                   newRoll);
            clearInputBuffer();
            return;
        }
    }

    /* Read the name (fgets allows names with spaces) */
    printf("Enter student name: ");
    clearInputBuffer();
    if (fgets(names[studentCount], NAME_LENGTH, stdin) == NULL)
    {
        printf("Could not read the name. Student not added.\n");
        return;
    }

    length = (int)strlen(names[studentCount]);
    if (length > 0 && names[studentCount][length - 1] == '\n')
    {
        names[studentCount][length - 1] = '\0';  /* remove Enter key */
        length--;
    }
    else
    {
        clearInputBuffer();  /* name was longer than the array */
    }

    if (length == 0)
    {
        printf("Name cannot be empty. Student not added.\n");
        return;
    }

    /* Read five marks. Each mark must be from 0 to 100. */
    for (s = 0; s < SUBJECTS; s++)
    {
        do
        {
            printf("Enter marks for subject %d (0-100): ", s + 1);

            if (scanf("%d", &mark) != 1)
            {
                printf("Please enter a number.\n");
                clearInputBuffer();
                mark = -1;
            }
            else if (mark < 0 || mark > 100)
            {
                printf("Marks must be between 0 and 100. Try again.\n");
            }
        } while (mark < 0 || mark > 100);

        marks[studentCount][s] = mark;
    }

    /* Store the roll number and calculate the grade */
    rollNumbers[studentCount] = newRoll;
    calculateGrade(studentCount);
    studentCount++;

    printf("\nStudent added successfully. Total students: %d\n", studentCount);
}

/* ============================================================
   FEATURE 2 and 3: DISPLAY ALL STUDENTS
   Total, average and grade are calculated automatically.
   ============================================================ */
void displayStudents(void)
{
    int i, s;
    int total;
    float average;

    if (studentCount == 0)
    {
        printf("\nNo students registered yet. Please add a student first.\n");
        return;
    }

    printf("\n----- ALL STUDENTS -----\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-8s %-30s %6s %6s %6s %6s %6s %8s %9s %6s\n",
           "Roll", "Name", "M1", "M2", "M3", "M4", "M5",
           "Total", "Average", "Grade");
    printf("----------------------------------------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++)
    {
        calculateGrade(i);
        total = calculateTotal(i);
        average = calculateAverage(i);

        printf("%-8d %-30s", rollNumbers[i], names[i]);
        for (s = 0; s < SUBJECTS; s++)
        {
            printf(" %6d", marks[i][s]);
        }
        printf(" %8d %9.2f %6s\n", total, average, grades[i]);
    }
    printf("----------------------------------------------------------------------------------------\n");
    printf("Total students: %d\n", studentCount);
}

/* ============================================================
   FEATURE 4: SEARCH STUDENT BY ROLL NUMBER
   Uses a simple linear search.
   ============================================================ */
void searchStudent(void)
{
    int target;
    int i, s;
    int found = 0;
    int total;
    float average;

    if (studentCount == 0)
    {
        printf("\nNo students registered yet. Please add a student first.\n");
        return;
    }

    printf("\nEnter roll number to search: ");
    if (scanf("%d", &target) != 1)
    {
        printf("Invalid roll number.\n");
        clearInputBuffer();
        return;
    }

    for (i = 0; i < studentCount; i++)
    {
        if (rollNumbers[i] == target)
        {
            found = 1;
            calculateGrade(i);
            total = calculateTotal(i);
            average = calculateAverage(i);

            printf("\n----- STUDENT FOUND -----\n");
            printf("Name       : %s\n", names[i]);
            printf("Roll Number: %d\n", rollNumbers[i]);
            printf("Marks      : ");
            for (s = 0; s < SUBJECTS; s++)
            {
                printf("%d  ", marks[i][s]);
            }
            printf("\nTotal      : %d\n", total);
            printf("Average    : %.2f\n", average);
            printf("Grade      : %s\n", grades[i]);
            break;  /* stop searching after the first match */
        }
    }

    if (found == 0)
    {
        printf("\nNo student found with roll number %d.\n", target);
    }
}

/* ============================================================
   FEATURE 5: SORT STUDENTS BY TOTAL MARKS
   Simple bubble sort in descending order. Every array is
   swapped together so all details of a student stay together.
   ============================================================ */
void sortStudents(void)
{
    int i, j, s;
    int tempNumber;
    int tempMark;
    char tempName[NAME_LENGTH];
    char tempGrade[4];

    if (studentCount == 0)
    {
        printf("\nNo students registered yet. Nothing to sort.\n");
        return;
    }

    for (i = 0; i < studentCount - 1; i++)
    {
        for (j = 0; j < studentCount - i - 1; j++)
        {
            if (calculateTotal(j) < calculateTotal(j + 1))
            {
                /* Swap names */
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);

                /* Swap roll numbers */
                tempNumber = rollNumbers[j];
                rollNumbers[j] = rollNumbers[j + 1];
                rollNumbers[j + 1] = tempNumber;

                /* Swap all five marks */
                for (s = 0; s < SUBJECTS; s++)
                {
                    tempMark = marks[j][s];
                    marks[j][s] = marks[j + 1][s];
                    marks[j + 1][s] = tempMark;
                }

                /* Swap grades */
                strcpy(tempGrade, grades[j]);
                strcpy(grades[j], grades[j + 1]);
                strcpy(grades[j + 1], tempGrade);
            }
        }
    }

    printf("\nStudents sorted by total marks (highest first).\n");
    printf("Use option 2 to view the sorted list.\n");
}
