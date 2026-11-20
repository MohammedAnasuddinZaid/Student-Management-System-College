# Student Management System

**GRIET – B.Tech First Year – PPS GLOB Mini Project**

A small, beginner-friendly C program that manages student marks using arrays.

---

## 1. Project Title

**Student Management System**

---

## 2. Introduction

This project is a simple terminal-based application written in the C programming language. It allows a user to add student details, view all students, search for a student by roll number, and sort students by their total marks.

The program is designed for a first-year B.Tech student. All the logic is written using basic C concepts such as variables, arrays, loops, conditions and functions. Student records are kept in arrays while the program is running. The data is not saved permanently, so it disappears when the program is closed.

---

## 3. Problem Statement

Colleges need a simple way to keep student marks and quickly find or arrange student records. Manually maintaining marks on paper is slow and can lead to mistakes such as duplicate roll numbers, wrong totals or incorrect grades.

The task is to build a small C program that:

- stores details of up to 50 students,
- prevents duplicate roll numbers,
- checks that marks are between 0 and 100,
- automatically calculates total, average and grade,
- allows searching and sorting of records,
- presents everything through a simple menu.

---

## 4. Objectives

1. To store name, roll number and five subject marks using arrays.
2. To add multiple students with validation of roll number and marks.
3. To calculate total marks, average marks and grade automatically.
4. To display all students in a neat table.
5. To search a student using a simple linear search.
6. To sort students in descending order of total marks using bubble sort.
7. To keep the code simple enough to explain line by line in a viva.

---

## 5. Software Requirements

| Item | Requirement |
|------|-------------|
| Programming language | C |
| Standard libraries | `stdio.h`, `string.h` |
| Compiler | GCC (any recent version) or Turbo C / Code::Blocks |
| Operating system | Windows, Linux, macOS or Termux |
| Editor | Any plain text editor (VS Code, Notepad, gedit, vi) |
| Hardware | Any basic computer or laptop |

No database, no GUI, no external library and no internet connection is required.

---

## 6. Concepts of C Used

- Variables and basic data types: `int`, `float`, `char`
- One-dimensional arrays: `rollNumbers[]`, `grades[]`
- Two-dimensional arrays: `names[][]` and `marks[][]`
- Character arrays (strings) and `string.h` functions `strlen()` and `strcpy()`
- Standard input/output: `printf()`, `scanf()`, `fgets()`, `getchar()`
- Operators: `+`, `<`, `>`, `>=`, `==`, `&&`, `||`
- Conditional statements: `if`, `else if`, `else`, `switch`
- Loops: `for`, `while`, `do-while`
- User-defined functions and function prototypes
- Constants using `#define`
- Basic searching (linear search)
- Basic sorting (bubble sort)

The program does **not** use pointers, structures, unions, dynamic memory, files, recursion or any advanced feature.

---

## 7. Algorithm

### Main algorithm

1. Start.
2. Display the menu.
3. Read the user's choice.
4. Using `switch`, call the matching function:
   - 1 → `addStudent()`
   - 2 → `displayStudents()`
   - 3 → `searchStudent()`
   - 4 → `sortStudents()`
   - 5 → exit the program
5. For an invalid choice, print an error and show the menu again.
6. Stop.

### addStudent()

1. Check if the number of students is 50. If yes, print a message and stop.
2. Read the roll number. It must be a positive number.
3. Compare it with all existing roll numbers. If it already exists, reject it.
4. Read the name using `fgets()` so that names with spaces are accepted.
5. Read five marks one by one. Each mark must be between 0 and 100; otherwise ask again.
6. Store the values in the arrays and increase `studentCount` by 1.

### displayStudents()

1. If there are no students, print a message and stop.
2. Print the table heading.
3. For every student, calculate total, average and grade, then print one row.

### searchStudent()

1. If there are no students, print a message and stop.
2. Read the roll number to search.
3. Check each roll number from index 0 to `studentCount - 1` (linear search).
4. If found, print all details of that student and stop searching.
5. If the loop finishes without a match, print "No student found".

### sortStudents()

1. If there are no students, print a message and stop.
2. Repeat passes using bubble sort.
3. Compare the totals of two neighbouring students.
4. If the left student has fewer marks, swap the name, roll number, all five marks and grade.
5. After all passes, the student with the highest total is first.

---

## 8. Simple Flowchart

```
                 +-----------------+
                 |      START      |
                 +--------+--------+
                          |
                  +-------v--------+
                  |  Display menu  |
                  +-------+--------+
                          |
                  +-------v--------+
                  |  Read choice   |
                  +-------+--------+
                          |
      +-------------------+-------------------+
      |          |          |          |      |
    choice=1   choice=2   choice=3   choice=4  choice=5
      |          |          |          |        |
 +----v----+ +---v----+ +---v----+ +---v----+ +--v--+
 |  Add    | | Display| | Search | |  Sort  | |Exit |
 | Student | |  All   | | Student| | Students| |     |
 +----+----+ +---+----+ +---+----+ +---+----+ +--+--+
      |          |          |          |        |
      +----------+----------+----------+        |
                          |                     |
                  +-------v--------+             |
                  | Show menu again|<------------+
                  +-------+--------+
                          |
                        STOP
```

---

## 9. Explanation of Each Function

| Function | What it does |
|----------|--------------|
| `main()` | Prints the menu, reads the choice and uses `switch` to call the correct function. It also handles invalid input. |
| `clearInputBuffer()` | Removes leftover characters (like the Enter key) from the input buffer so that the next read works correctly. |
| `calculateTotal(index)` | Adds the five marks of one student and returns the total. |
| `calculateAverage(index)` | Calls `calculateTotal()` and divides the result by 5.0 to get the average. |
| `calculateGrade(index)` | Finds the grade from the average and stores `"A+"`, `"A"`, `"B"`, `"C"`, `"D"` or `"F"` in the global `grades` array. |
| `addStudent()` | Checks capacity, duplicate roll number and marks, then stores a new student in the arrays. |
| `displayStudents()` | Prints all students in a table with name, roll number, five marks, total, average and grade. |
| `searchStudent()` | Reads a roll number, performs linear search and prints the matching student or a "not found" message. |
| `sortStudents()` | Uses bubble sort to arrange students from highest total to lowest total. All related arrays are swapped together. |

### Grading rule

| Average | Grade |
|---------|-------|
| 90 – 100 | A+ |
| 80 – 89 | A |
| 70 – 79 | B |
| 60 – 69 | C |
| 50 – 59 | D |
| Below 50 | F |

---

## 10. Sample Input and Output

### Sample input

```
1
103
Rahul Kumar
55
60
58
62
57
1
101
Anas Zaid
95
92
88
91
90
2
3
101
3
999
4
2
5
```

### Sample output

```
========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
----- ADD STUDENT -----
Enter roll number: Enter student name: Enter marks for subject 1 (0-100): Enter marks for subject 2 (0-100): Enter marks for subject 3 (0-100): Enter marks for subject 4 (0-100): Enter marks for subject 5 (0-100):
Student added successfully. Total students: 1

========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
----- ADD STUDENT -----
Enter roll number: Enter student name: Enter marks for subject 1 (0-100): Enter marks for subject 2 (0-100): Enter marks for subject 3 (0-100): Enter marks for subject 4 (0-100): Enter marks for subject 5 (0-100):
Student added successfully. Total students: 2

========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
----- ALL STUDENTS -----
----------------------------------------------------------------------------------------
Roll     Name                               M1     M2     M3     M4     M5    Total   Average  Grade
----------------------------------------------------------------------------------------
103      Rahul Kumar                        55     60     58     62     57      292     58.40      D
101      Anas Zaid                          95     92     88     91     90      456     91.20     A+
----------------------------------------------------------------------------------------
Total students: 2

========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
Enter roll number to search:
----- STUDENT FOUND -----
Name       : Anas Zaid
Roll Number: 101
Marks      : 95  92  88  91  90
Total      : 456
Average    : 91.20
Grade      : A+

========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
Enter roll number to search:
No student found with roll number 999.

========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
Students sorted by total marks (highest first).
Use option 2 to view the sorted list.

========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
----- ALL STUDENTS -----
----------------------------------------------------------------------------------------
Roll     Name                               M1     M2     M3     M4     M5    Total   Average  Grade
----------------------------------------------------------------------------------------
101      Anas Zaid                          95     92     88     91     90      456     91.20     A+
103      Rahul Kumar                        55     60     58     62     57      292     58.40      D
----------------------------------------------------------------------------------------
Total students: 2

========================================
       STUDENT MANAGEMENT SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Sort Students by Total Marks
5. Exit
----------------------------------------
Enter your choice:
Thank you for using Student Management System.
Program exited. Goodbye!
```

---

## 11. Advantages

1. Very easy to understand and explain to faculty.
2. Uses only basic C features taught in the first year.
3. Runs in any simple terminal; no special software needed.
4. Validates duplicate roll numbers and marks.
5. Calculates total, average and grade automatically.
6. Search and sorting are simple and easy to demonstrate.

---

## 12. Limitations

1. Data is stored only in arrays, so all records are lost when the program exits.
2. Only 50 students can be stored.
3. Roll numbers must be numeric.
4. A name longer than 29 characters is cut short.
5. Only five fixed subjects are supported.
6. Only one student is shown at a time during search; there is no delete or edit option.

---

## 13. Future Scope

If the basics are clear, the following improvements can be made later (not included in this project):

- Save records to a text file so they remain after the program closes.
- Add options to modify or delete a student.
- Make the number of subjects configurable.
- Use structures to store all details of one student together.
- Add more detailed statistics such as class average or topper.

---

## 14. Conclusion

The Student Management System successfully demonstrates how arrays, loops, conditions and functions can be used together to build a useful program. It covers adding, displaying, searching and sorting student records with simple validation. The project is deliberately kept small so that every line of code can be understood and explained confidently in a college presentation.

---

## How to Compile and Run

**Linux / macOS / Termux:**

```bash
gcc main.c -o sms
./sms
```

**Windows (MinGW / Code::Blocks):**

```bash
gcc main.c -o sms.exe
sms.exe
```

Extra warnings check (optional):

```bash
gcc main.c -o sms -Wall -Wextra -Wpedantic -std=c11
```

---

## Testing Done

| Test case | Result |
|-----------|--------|
| Display with no students | Shows a proper message |
| Search with no students | Shows a proper message |
| Sort with no students | Shows a proper message |
| Add multiple students | Passed |
| Duplicate roll number | Rejected |
| Marks below 0 or above 100 | Rejected, user asked to re-enter |
| Non-numeric input | Handled with an error message |
| Search existing roll number | Full details displayed |
| Search missing roll number | "No student found" displayed |
| Sort by total marks | Highest total appears first |
| Display after sorting | Order is correct |
| 50 students added | Passed |
| 51st student | Rejected with capacity message |
| Grade boundaries (90, 80, 70, 60, 50, below 50) | Correct grades A+, A, B, C, D, F |
