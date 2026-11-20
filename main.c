/*
 * ============================================================
 *  STUDENT MANAGEMENT SYSTEM
 *  GRIET - B.Tech First Year - PPS GLOB Mini Project
 * ============================================================
 *
 *  A simple terminal program written in C.
 *
 *  Student details are kept in arrays while the program is
 *  running. They are not saved after the program is closed.
 *
 *  Only basic C is used here:
 *  - variables and one-dimensional / two-dimensional arrays
 *  - character arrays for names
 *  - printf(), fgets(), getchar()
 *  - if / else, switch, for and while loops
 *  - user-defined functions
 *
 *  No pointers, structures, files, dynamic memory or recursion
 *  are used.
 */

#include <stdio.h>
#include <string.h>

/* ---------- Constants ---------- */
#define MAX_STUDENTS 50       /* maximum number of students        */
#define NAME_LENGTH 30        /* 29 characters + null character    */
#define SUBJECTS 5            /* five subjects                     */
#define MAX_ROLL 999999999    /* largest roll number accepted      */
#define INPUT_LENGTH 200      /* size of the input line buffer     */

/* ---------- Global student arrays ----------
   The arrays are global so that every function can use the
   same data without passing pointers between functions. */
int studentCount = 0;
char names[MAX_STUDENTS][NAME_LENGTH];
int rollNumbers[MAX_STUDENTS];
int marks[MAX_STUDENTS][SUBJECTS];
char grades[MAX_STUDENTS][4];     /* "A+", "A", "B", "C", "D", "F" */

/* ---------- Global input buffer ----------
   One complete line is read here first. The line is then
   checked before its value is used. */
char inputLine[INPUT_LENGTH];
int inputClosed = 0;              /* becomes 1 when input ends */

/* ---------- Function prototypes ---------- */
void clearInputBuffer(void);
int readInputLine(void);
int readNumber(void);
void trimSpaces(void);
int nameHasLetter(void);
int calculateTotal(int index);
float calculateAverage(int index);
void calculateGrade(int index);
void printTableLine(void);
void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void sortStudents(void);

/* ============================================================
   MAIN FUNCTION
   This function only shows the menu and calls the right
   feature function with a switch statement.
   ============================================================ */
int main(void)
{
    int choice;

    printf("\n========================================\n");
    printf("       STUDENT MANAGEMENT SYSTEM\n");
    printf("========================================\n");

    while (inputClosed == 0)
    {
        printf("\n1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Sort Students by Total Marks\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        choice = readNumber();

        if (inputClosed == 1)
        {
            break;
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
                printf("\nThank you for using the Student Management System.\n");
                printf("Program exited. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice. Please enter a number from 1 to 5.\n");
        }
    }

    printf("\nNo more input. Program closed.\n");
    return 0;
}

/* ============================================================
   Removes the characters that are still waiting in the input
   buffer. This is used when a line is longer than the buffer.
   ============================================================ */
void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* throw the extra characters away */
    }
}

/* ============================================================
   Reads one full line into inputLine and removes the newline.
   Returns 1 on success and 0 when there is no more input.
   ============================================================ */
int readInputLine(void)
{
    int length;

    if (inputClosed == 1)
    {
        return 0;
    }

    if (fgets(inputLine, INPUT_LENGTH, stdin) == NULL)
    {
        inputClosed = 1;
        return 0;
    }

    length = (int)strlen(inputLine);

    if (length > 0 && inputLine[length - 1] == '\n')
    {
        inputLine[length - 1] = '\0';
    }
    else
    {
        /* The line was too long, so remove the rest of it. */
        clearInputBuffer();
    }

    /* Remove the carriage return if the input came from a
       Windows text file with CRLF line endings. */
    length = (int)strlen(inputLine);

    if (length > 0 && inputLine[length - 1] == '\r')
    {
        inputLine[length - 1] = '\0';
    }

    return 1;
}

/* ============================================================
   Converts inputLine into a whole number.
   Returns -1 if the line is empty, has letters, has extra
   characters or is too large.
   ============================================================ */
int readNumber(void)
{
    int i = 0;
    int number = 0;
    int digits = 0;

    if (readInputLine() == 0)
    {
        return -1;
    }

    /* skip spaces before the number */
    while (inputLine[i] == ' ' || inputLine[i] == '\t')
    {
        i++;
    }

    /* skip extra leading zeroes, but keep one digit */
    while (inputLine[i] == '0' &&
           inputLine[i + 1] >= '0' && inputLine[i + 1] <= '9')
    {
        i++;
    }

    /* read the digits and build the number */
    while (inputLine[i] >= '0' && inputLine[i] <= '9')
    {
        if (number > MAX_ROLL / 10)
        {
            return -1;       /* the number is too large */
        }

        number = number * 10 + (inputLine[i] - '0');
        digits++;
        i++;
    }

    if (digits == 0)
    {
        return -1;           /* there was no number at all */
    }

    if (number > MAX_ROLL)
    {
        return -1;
    }

    /* only spaces or tabs may follow the number */
    while (inputLine[i] == ' ' || inputLine[i] == '\t')
    {
        i++;
    }

    if (inputLine[i] != '\0')
    {
        return -1;           /* something like 12abc was entered */
    }

    return number;
}

/* ============================================================
   Removes spaces and tabs from the beginning and the end of
   inputLine. Spaces inside the name are kept.
   ============================================================ */
void trimSpaces(void)
{
    int start = 0;
    int end;
    int i;

    while (inputLine[start] == ' ' || inputLine[start] == '\t')
    {
        start++;
    }

    end = (int)strlen(inputLine) - 1;

    while (end >= start &&
          (inputLine[end] == ' ' || inputLine[end] == '\t'))
    {
        end--;
    }

    for (i = 0; start + i <= end; i++)
    {
        inputLine[i] = inputLine[start + i];
    }

    inputLine[i] = '\0';
}

/* ============================================================
   Checks that a name has at least one letter. This stops
   inputs such as "12345" from being accepted as a name.
   ============================================================ */
int nameHasLetter(void)
{
    int i;
    char ch;

    for (i = 0; inputLine[i] != '\0'; i++)
    {
        ch = inputLine[i];

        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (unsigned char)ch >= 128)
        {
            return 1;
        }
    }

    return 0;
}

/* ============================================================
   Adds the five marks of one student and returns the total.
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
   5.0f keeps the decimal part of the answer. The (float) cast
   shows clearly that the total is converted to a floating-point
   value before the division.
   ============================================================ */
float calculateAverage(int index)
{
    return (float)calculateTotal(index) / 5.0f;
}

/* ============================================================
   Finds the grade from the average and stores it in the
   grades array.
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
   Prints one separator line for the student table.
   The table is 79 characters wide.
   ============================================================ */
void printTableLine(void)
{
    int i;

    for (i = 0; i < 79; i++)
    {
        printf("-");
    }

    printf("\n");
}

/* ============================================================
   FEATURE 1: ADD STUDENT
   Reads and checks the roll number, name and five marks.
   Values are kept in local variables until every input is valid,
   and the student count is increased only after that.
   ============================================================ */
void addStudent(void)
{
    int index;
    int newRoll;
    int i;
    int s;
    int mark;
    char newName[NAME_LENGTH];
    int newMarks[SUBJECTS];

    printf("\n----- ADD STUDENT -----\n");

    /* stop before the arrays become full */
    if (studentCount >= MAX_STUDENTS)
    {
        printf("The list is full. You cannot add more than %d students.\n",
               MAX_STUDENTS);
        return;
    }

    index = studentCount;

    index = studentCount;

    /* ---------- roll number ---------- */
    newRoll = 0;

    while (newRoll == 0)
    {
        printf("Enter roll number (1 to %d): ", MAX_ROLL);
        newRoll = readNumber();

        if (inputClosed == 1)
        {
            return;
        }

        if (newRoll < 1 || newRoll > MAX_ROLL)
        {
            printf("Invalid roll number. Enter a whole number from 1 to %d.\n",
                   MAX_ROLL);
            newRoll = 0;
            continue;
        }

        /* linear search for a duplicate roll number */
        for (i = 0; i < studentCount; i++)
        {
            if (rollNumbers[i] == newRoll)
            {
                printf("Roll number %d is already used. Try another number.\n",
                       newRoll);
                newRoll = 0;
                break;
            }
        }
    }

    /* ---------- name ---------- */
    while (1)
    {
        printf("Enter student name (up to %d characters): ",
               NAME_LENGTH - 1);

        if (readInputLine() == 0)
        {
            return;
        }

        trimSpaces();

        if (inputLine[0] == '\0')
        {
            printf("Name cannot be empty. Try again.\n");
            continue;
        }

        if ((int)strlen(inputLine) > NAME_LENGTH - 1)
        {
            printf("Name is too long. Maximum %d characters allowed.\n",
                   NAME_LENGTH - 1);
            continue;
        }

        if (nameHasLetter() == 0)
        {
            printf("Name must contain at least one letter. Try again.\n");
            continue;
        }

        break;
    }

    strcpy(newName, inputLine);

    /* ---------- five subject marks ---------- */
    for (s = 0; s < SUBJECTS; s++)
    {
        while (1)
        {
            printf("Enter marks for subject %d (0 to 100): ", s + 1);
            mark = readNumber();

            if (inputClosed == 1)
            {
                return;
            }

            if (mark < 0 || mark > 100)
            {
                printf("Invalid marks. Enter a whole number from 0 to 100.\n");
                continue;
            }

            break;
        }

        newMarks[s] = mark;
    }

    /* ---------- save the student ---------- */
    index = studentCount;
    strcpy(names[index], newName);
    rollNumbers[index] = newRoll;

    for (s = 0; s < SUBJECTS; s++)
    {
        marks[index][s] = newMarks[s];
    }

    calculateGrade(index);
    studentCount++;

    printf("\nStudent added successfully.\n");
    printf("Total students : %d\n", studentCount);
    printf("Total marks    : %d\n", calculateTotal(index));
    printf("Average marks  : %.2f\n", calculateAverage(index));
    printf("Grade          : %s\n", grades[index]);
}

/* ============================================================
   FEATURE 2 and 3: DISPLAY ALL STUDENTS
   Total, average and grade are calculated automatically.
   ============================================================ */
void displayStudents(void)
{
    int i;
    int s;
    int total;
    float average;

    printf("\n----- ALL STUDENTS -----\n");

    if (studentCount == 0)
    {
        printf("No students registered yet. Add a student first.\n");
        return;
    }

    printTableLine();
    printf("%-9s %-29s %3s %3s %3s %3s %3s %5s %7s %-5s\n",
           "Roll", "Name", "M1", "M2", "M3", "M4", "M5",
           "Total", "Average", "Grade");
    printTableLine();

    for (i = 0; i < studentCount; i++)
    {
        calculateGrade(i);
        total = calculateTotal(i);
        average = calculateAverage(i);

        printf("%-9d %-29s", rollNumbers[i], names[i]);

        for (s = 0; s < SUBJECTS; s++)
        {
            printf(" %3d", marks[i][s]);
        }

        printf(" %5d %7.2f %-5s\n", total, average, grades[i]);
    }

    printTableLine();
    printf("Total students: %d\n", studentCount);
}

/* ============================================================
   FEATURE 4: SEARCH STUDENT BY ROLL NUMBER
   Uses a simple linear search from the first student.
   ============================================================ */
void searchStudent(void)
{
    int target;
    int i;
    int s;
    int found = 0;
    int total;
    float average;

    printf("\n----- SEARCH STUDENT -----\n");

    if (studentCount == 0)
    {
        printf("No students registered yet. Add a student first.\n");
        return;
    }

    while (1)
    {
        printf("Enter roll number to search: ");
        target = readNumber();

        if (inputClosed == 1)
        {
            return;
        }

        if (target < 1 || target > MAX_ROLL)
        {
            printf("Invalid roll number. Enter a whole number from 1 to %d.\n",
                   MAX_ROLL);
            continue;
        }

        break;
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
            printf("Name        : %s\n", names[i]);
            printf("Roll Number : %d\n", rollNumbers[i]);

            for (s = 0; s < SUBJECTS; s++)
            {
                printf("Subject %d   : %d\n", s + 1, marks[i][s]);
            }

            printf("Total       : %d\n", total);
            printf("Average     : %.2f\n", average);
            printf("Grade       : %s\n", grades[i]);
            break;
        }
    }

    if (found == 0)
    {
        printf("\nNo student found with roll number %d.\n", target);
    }
}

/* ============================================================
   FEATURE 5: SORT STUDENTS BY TOTAL MARKS
   Simple bubble sort in descending order. The name, roll
   number, all five marks and the grade move together.
   ============================================================ */
void sortStudents(void)
{
    int i;
    int j;
    int s;
    int tempRoll;
    int tempMark;
    char tempName[NAME_LENGTH];
    char tempGrade[4];

    printf("\n----- SORT BY TOTAL MARKS -----\n");

    if (studentCount == 0)
    {
        printf("No students registered yet. Nothing to sort.\n");
        return;
    }

    if (studentCount == 1)
    {
        printf("Only one student is registered, so the list is already sorted.\n");
        return;
    }

    for (i = 0; i < studentCount - 1; i++)
    {
        for (j = 0; j < studentCount - i - 1; j++)
        {
            if (calculateTotal(j) < calculateTotal(j + 1))
            {
                /* swap names */
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);

                /* swap roll numbers */
                tempRoll = rollNumbers[j];
                rollNumbers[j] = rollNumbers[j + 1];
                rollNumbers[j + 1] = tempRoll;

                /* swap all five marks */
                for (s = 0; s < SUBJECTS; s++)
                {
                    tempMark = marks[j][s];
                    marks[j][s] = marks[j + 1][s];
                    marks[j + 1][s] = tempMark;
                }

                /* swap grades */
                strcpy(tempGrade, grades[j]);
                strcpy(grades[j], grades[j + 1]);
                strcpy(grades[j + 1], tempGrade);
            }
        }
    }

    printf("Students sorted by total marks. Highest total is first.\n");
    displayStudents();
}
