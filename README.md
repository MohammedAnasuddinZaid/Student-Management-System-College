# Student Management System

**GRIET - B.Tech First Year - PPS GLOB Mini Project**

| Item | Details |
|------|---------|
| Project | Student Management System |
| Language | C (C11) |
| Compiler tested | GCC 16.1.0 (MinGW) |
| Storage | Arrays in RAM |
| Maximum students | 50 |
| Interface | Terminal menu |

A small menu-driven program to add, display, search and sort student marks.

**Project files**

| File | Purpose |
|------|---------|
| `main.c` | Complete C source code |
| `README.md` | Project report and documentation |
| `VIVA_QUESTIONS.md` | Likely viva questions with simple answers |

---

## 1. Project Title

**Student Management System**

---

## 2. Introduction

This project is a terminal-based Student Management System written only in C. It keeps the name, roll number and marks of five subjects for each student. The user can add students, view all records in a table, search for a student by roll number and sort students by total marks.

The program automatically calculates the total marks, average marks and grade. It also checks the input before storing anything. For example, a duplicate roll number is not allowed and a mark outside 0 to 100 is rejected.

Student records are stored in ordinary arrays while the program is running. They are not saved to a file, so the list becomes empty when the program is closed. This is explained again in the Limitations section.

The code uses only the C concepts taught in the first year: variables, arrays, character arrays, loops, conditions, functions and two standard headers (`stdio.h` and `string.h`). No pointers, structures, unions, dynamic memory, linked lists, recursion or advanced file handling are used.

---

## 3. Problem Statement

In a college, student marks are often maintained in a paper register. This creates a few common problems:

- The same roll number may be entered twice by mistake.
- Total marks and averages may be calculated wrongly.
- Searching for one student in a long register takes time.
- Arranging students according to marks is slow.
- A mark such as 105 can be written by mistake and nobody notices immediately.

The task is to build a small C program that stores student details in arrays and performs these operations through a simple menu. The program must validate the input, calculate the results automatically and keep the code easy to understand.

---

## 4. Objectives

1. To store the name, roll number and five subject marks of a student using arrays.
2. To allow up to 50 students to be added during one run.
3. To prevent duplicate roll numbers.
4. To accept only whole-number marks from 0 to 100.
5. To calculate total marks, average marks and grade automatically.
6. To display all students in a clean table.
7. To search for a student using linear search.
8. To sort students in descending order of total marks using bubble sort.
9. To handle wrong input and an empty student list without crashing.
10. To keep every function simple enough to explain in a viva.

---

## 5. Software Requirements

| Item | Requirement |
|------|-------------|
| Programming language | C |
| Standard headers | `stdio.h`, `string.h` |
| Compiler | GCC (MinGW on Windows) or Code::Blocks |
| Operating system | Windows, Linux or macOS |
| Interface | Any terminal or command prompt |
| Editor | VS Code, Notepad, gedit or any text editor |
| Hardware | Any basic computer or laptop |

No database, GUI, browser, external library or internet connection is needed.

---

## 6. Concepts of C Used

| Concept | Where it is used |
|---------|------------------|
| `int`, `float`, `char` | Roll numbers, marks, averages and characters |
| One-dimensional arrays | `rollNumbers[50]`, `grades[50]` |
| Two-dimensional arrays | `names[50][30]`, `marks[50][5]` |
| Character arrays (strings) | Student names and grades |
| `strlen()` | Finding the length of the input line or name |
| `strcpy()` | Copying a name or grade into an array |
| `printf()` | Showing the menu, prompts and tables |
| `fgets()` | Reading one complete line of input |
| `getchar()` | Removing extra characters from a long line |
| Operators | Arithmetic, comparison and logical operators |
| `if`, `else if`, `else` | Validation and grade selection |
| `switch` | Selecting a menu option |
| `for` loop | Displaying marks and sorting |
| `while` loop | Repeating a prompt until the input is valid |
| User-defined functions | One function for each task |
| Function prototypes | Declarations written before `main()` |
| `#define` constants | `MAX_STUDENTS`, `NAME_LENGTH`, `SUBJECTS` |
| Linear search | Finding a roll number |
| Bubble sort | Arranging students by total marks |
| Type casting | `(float)` before dividing the total by 5.0 |

The program does **not** use pointers, structures, unions, dynamic memory, files, recursion or function pointers.

---

## 7. Program Structure

### 7.1 Data stored in arrays

All student data is kept in global arrays. This allows every function to use the same data without passing pointers.

| Variable | Declaration | Meaning |
|----------|-------------|---------|
| `studentCount` | `int studentCount` | Number of students currently stored |
| `names` | `char names[50][30]` | 50 names, each up to 29 characters plus `'\0'` |
| `rollNumbers` | `int rollNumbers[50]` | One roll number for each student |
| `marks` | `int marks[50][5]` | Five subject marks for each student |
| `grades` | `char grades[50][4]` | Grade text such as `"A+"` or `"F"` |

`studentCount` is also the index where the next student will be stored. It starts at 0 and increases by one after a successful add.

### 7.2 Input handling

The program reads every input as a complete line using `fgets()`. The line is first stored in the global array `inputLine[200]`. Small helper functions then check it:

- `readInputLine()` removes the newline and detects the end of input.
- `readNumber()` converts the line into a whole number and rejects bad values.
- `trimSpaces()` removes spaces and tabs from the ends of a name.
- `nameHasLetter()` makes sure a name is not just numbers or punctuation.

This is done so that inputs like `12abc`, `1.5`, a blank line or a very large number can be rejected safely. It also avoids the leftover newline problem that happens when `scanf()` and `fgets()` are mixed.

### 7.3 Functions

| Function | Work |
|----------|------|
| `main()` | Shows the menu, reads the choice and calls the correct function |
| `clearInputBuffer()` | Throws away extra characters after a long input line |
| `readInputLine()` | Reads one line and removes the newline |
| `readNumber()` | Converts a line to a valid whole number or returns -1 |
| `trimSpaces()` | Removes leading and trailing spaces from a name |
| `nameHasLetter()` | Checks that the name has at least one letter |
| `calculateTotal()` | Adds the five subject marks |
| `calculateAverage()` | Divides the total by 5.0 |
| `calculateGrade()` | Chooses the grade from the average |
| `printTableLine()` | Prints the 79-character line used in the table |
| `addStudent()` | Reads and stores one new student |
| `displayStudents()` | Shows all students in a table |
| `searchStudent()` | Finds a student by roll number |
| `sortStudents()` | Sorts students by total marks and shows the result |

`main()` contains only the menu, the input read and a `switch`. The actual work is done by the feature functions.

---

## 8. Algorithm

### 8.1 Main algorithm

1. Start.
2. Print the project heading.
3. Print the menu.
4. Read the user's choice using `readNumber()`.
5. If no more input is available, close the program.
6. Use `switch` to call the matching function:
   - 1: `addStudent()`
   - 2: `displayStudents()`
   - 3: `searchStudent()`
   - 4: `sortStudents()`
   - 5: exit the program
7. If the choice is not from 1 to 5, print an error message.
8. Repeat from step 3 until the user chooses 5 or the input ends.

### 8.2 `addStudent()`

1. If `studentCount` is 50, print a capacity message and return.
2. Read a roll number. It must be a whole number from 1 to 999999999.
3. Compare the roll number with all existing roll numbers. If it is already present, print a message and ask again.
4. Read the name. Remove extra spaces from the ends.
5. Reject the name if it is empty, longer than 29 characters or has no letter.
6. Read five marks one by one.
7. Each mark must be a whole number from 0 to 100. Otherwise ask for the same subject again.
8. Store the name, roll number and marks.
9. Calculate the grade, increase `studentCount` and show a short summary.

### 8.3 `displayStudents()`

1. If `studentCount` is 0, print "No students registered yet" and return.
2. Print the table heading.
3. For every student, calculate total, average and grade.
4. Print one row for each student.
5. Print the total number of students.

### 8.4 `searchStudent()`

1. If the list is empty, print a message and return.
2. Read a roll number. Ask again if it is not valid.
3. Start from index 0 and compare each roll number with the target.
4. If a match is found, calculate the results and print the complete details.
5. Stop searching after the first match.
6. If no match is found, print "No student found".

### 8.5 `sortStudents()`

1. If the list is empty, print a message and return.
2. If there is only one student, print that the list is already sorted.
3. Use two nested `for` loops (bubble sort).
4. Compare the total of the current student with the next student.
5. If the current total is smaller, swap the two students.
6. Swap the name, roll number, all five marks and the grade together.
7. After sorting, display the new table.

### 8.6 Input validation

1. Read a full line.
2. Remove the newline.
3. For a number, skip leading spaces and leading zeroes, then read the digits.
4. Stop if the number becomes too large.
5. Allow only spaces or tabs after the number.
6. Return -1 if anything is wrong.
7. The caller asks again until a valid value is entered.

---

## 9. Simple Flowchart

```
              +-------------------+
              |       START       |
              +---------+---------+
                        |
              +---------v---------+
        +---->|   Display menu    |
        |     +---------+---------+
        |               |
        |     +---------v---------+
        |     |    Read choice    |
        |     +---------+---------+
        |               |
        |     +---------v---------+
        |     |  Choice 1 to 5?   |
        |     +----+---------+----+
        |          | no      | yes
        |          v         v
        |     +----+---+  +--+-----------+
        |     | Show   |  |  Choice 5?   |
        |     | error  |  +--+-------+---+
        |     +----+---+     | no    | yes
        |          |         v       v
        |          |  +------+---+  +---+
        |          |  | Run the  |  |STOP|
        |          |  | operation|  +---+
        |          |  | 1 to 4   |
        |          |  +------+---+
        |          |         |
        +----------+---------+
```

If the choice is not from 1 to 5, the program prints an error message and shows the menu again. Choices 1 to 4 do their work and then return to the menu.

---

## 10. Explanation of Each Function

| Function | Explanation |
|----------|-------------|
| `main()` | Prints the menu in a `while` loop, reads the choice, calls the selected function with `switch`, and exits when the user chooses 5 or the input ends. |
| `clearInputBuffer()` | Uses `getchar()` in a loop to remove characters left over after a line that was longer than 199 characters. |
| `readInputLine()` | Calls `fgets()` to read one line into `inputLine`. It removes `'\n'` and also removes `'\r'` if the input came from a Windows text file. If `fgets()` returns `NULL`, it sets `inputClosed = 1`. |
| `readNumber()` | Reads the global `inputLine` and converts it to a number using a loop. It rejects an empty line, letters, decimal points, plus or minus signs, extra characters and numbers larger than 999999999. It returns -1 for a bad value. |
| `trimSpaces()` | Finds the first and last non-space character in the name and shifts the name to the left. Spaces in the middle, like in "Rahul Kumar", are kept. |
| `nameHasLetter()` | Loops through the name and returns 1 if it finds an English letter or a byte from a non-English character set. This prevents a name like `12345` or `...` from being accepted. |
| `calculateTotal()` | Adds `marks[index][0]` to `marks[index][4]` with a `for` loop and returns the total. |
| `calculateAverage()` | Converts the total to `float` and divides by `5.0f`, so the decimal part is kept. |
| `calculateGrade()` | Checks the average against 90, 80, 70, 60 and 50, then copies the correct grade into `grades[index]`. |
| `printTableLine()` | Prints 79 hyphens. This keeps the table heading and rows aligned. |
| `addStudent()` | Checks the capacity, reads a unique roll number, reads a valid name, reads five valid marks, stores the values and shows the total, average and grade of the new student. |
| `displayStudents()` | Shows a message if the list is empty. Otherwise it prints the heading and one row per student with roll number, name, five marks, total, average and grade. |
| `searchStudent()` | Asks for a valid roll number, performs a linear search and shows all details of the matching student. If there is no match, it prints a not-found message. |
| `sortStudents()` | Performs bubble sort in descending order. It swaps every array so that one student's details do not get mixed with another student's details. It then calls `displayStudents()`. |

### Input checks and fallbacks

| Input | Rule | What happens if it is wrong |
|-------|------|-----------------------------|
| Menu choice | Whole number from 1 to 5 | Error message, then the menu is shown again |
| Roll number | Whole number from 1 to 999999999 | Error message and the roll number is asked again |
| Duplicate roll | Must not match an existing roll | Message and a different roll number is asked |
| Name | Not empty, maximum 29 characters, at least one letter | Message and the name is asked again |
| Marks | Whole number from 0 to 100 | Message and the same subject is asked again |
| Long input line | Maximum 199 characters are kept | Extra characters are thrown away, then the value is checked normally |
| Empty student list | No display, search or sort is possible | A clear message is printed |
| 51st student | Maximum capacity is 50 | Capacity message is printed before asking for details |
| End of input | `fgets()` returns `NULL` | `inputClosed` is set and the program closes without looping forever |

A student is counted only after the roll number, name and all five marks are valid.

---

## 11. Sample Input and Output

The menu is printed again after every operation. To keep this page short, the repeated menu is shown as `[menu]` after the first screen. The values typed by the user are shown after each prompt. In the table, M1 to M5 are the marks of the five subjects.

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
Enter your choice: 1

----- ADD STUDENT -----
Enter roll number (1 to 999999999): 103
Enter student name (up to 29 characters): Rahul Kumar
Enter marks for subject 1 (0 to 100): 55
Enter marks for subject 2 (0 to 100): 60
Enter marks for subject 3 (0 to 100): 58
Enter marks for subject 4 (0 to 100): 62
Enter marks for subject 5 (0 to 100): 57

Student added successfully.
Total students : 1
Total marks    : 292
Average marks  : 58.40
Grade          : D

[menu]
Enter your choice: 1

----- ADD STUDENT -----
Enter roll number (1 to 999999999): 101
Enter student name (up to 29 characters): Anas Zaid
Enter marks for subject 1 (0 to 100): 95
Enter marks for subject 2 (0 to 100): 92
Enter marks for subject 3 (0 to 100): 88
Enter marks for subject 4 (0 to 100): 91
Enter marks for subject 5 (0 to 100): 90

Student added successfully.
Total students : 2
Total marks    : 456
Average marks  : 91.20
Grade          : A+

[menu]
Enter your choice: 2

----- ALL STUDENTS -----
-------------------------------------------------------------------------------
Roll      Name                           M1  M2  M3  M4  M5 Total Average Grade
-------------------------------------------------------------------------------
103       Rahul Kumar                    55  60  58  62  57   292   58.40 D
101       Anas Zaid                      95  92  88  91  90   456   91.20 A+
-------------------------------------------------------------------------------
Total students: 2

[menu]
Enter your choice: 3

----- SEARCH STUDENT -----
Enter roll number to search: 101

----- STUDENT FOUND -----
Name        : Anas Zaid
Roll Number : 101
Subject 1   : 95
Subject 2   : 92
Subject 3   : 88
Subject 4   : 91
Subject 5   : 90
Total       : 456
Average     : 91.20
Grade       : A+

[menu]
Enter your choice: 3

----- SEARCH STUDENT -----
Enter roll number to search: 999

No student found with roll number 999.

[menu]
Enter your choice: 4

----- SORT BY TOTAL MARKS -----
Students sorted by total marks. Highest total is first.

----- ALL STUDENTS -----
-------------------------------------------------------------------------------
Roll      Name                           M1  M2  M3  M4  M5 Total Average Grade
-------------------------------------------------------------------------------
101       Anas Zaid                      95  92  88  91  90   456   91.20 A+
103       Rahul Kumar                    55  60  58  62  57   292   58.40 D
-------------------------------------------------------------------------------
Total students: 2

[menu]
Enter your choice: 5

Thank you for using the Student Management System.
Program exited. Goodbye!
```

### A few error examples

```
Enter your choice: abc

Invalid choice. Please enter a number from 1 to 5.

[menu]
Enter your choice: 1

----- ADD STUDENT -----
Enter roll number (1 to 999999999): 12abc
Invalid roll number. Enter a whole number from 1 to 999999999.
Enter roll number (1 to 999999999): 101
Roll number 101 is already used. Try another number.
Enter roll number (1 to 999999999): 105
Enter student name (up to 29 characters):
Name cannot be empty. Try again.
Enter student name (up to 29 characters): Test Name
Enter marks for subject 1 (0 to 100): 101
Invalid marks. Enter a whole number from 0 to 100.
Enter marks for subject 1 (0 to 100): 95
```

---

## 12. Advantages

1. The program is written only in standard C and uses only basic first-year concepts.
2. It runs in any terminal and does not need a database, browser or external library.
3. Duplicate roll numbers are stopped before they enter the list.
4. Names and marks are validated, so bad values do not spoil the records.
5. Total, average and grade are calculated automatically.
6. The table is aligned and easy to read during a demonstration.
7. Search and sort are simple and can be explained line by line.
8. Empty lists, wrong menu choices, long input lines and end of input are handled safely.
9. The code is divided into small functions, so each feature can be tested separately.
10. The size of the code is small enough to finish and practise before the presentation.

---

## 13. Limitations

1. Records are kept only in RAM. They are lost when the program is closed.
2. A maximum of 50 students can be stored in one run.
3. The roll number must be a number from 1 to 999999999. Text roll numbers such as `23B81A0501` are not supported.
4. A name can have at most 29 characters. Extra-long names are rejected.
5. The number of subjects is fixed at five.
6. There is no option to edit or delete a student.
7. Linear search and bubble sort are simple but not fast for very large lists. They are fine for 50 students.
8. There is no login, password or access control.
9. Only one user can use the terminal program at a time.
10. The program does not save a printed report or a CSV file.

---

## 14. Future Scope

1. Save records in a text file using `fopen()`, `fprintf()` and `fscanf()` so they remain after the program closes.
2. Add options to edit or delete a student.
3. Use structures so that all details of one student are kept in a single variable.
4. Allow the user to choose the number of subjects.
5. Show a class average, the highest mark and the topper.
6. Add sorting by name or roll number in addition to total marks.
7. Use binary search after sorting by roll number.
8. Add a simple login for a teacher.
9. Export marks to a CSV file that can be opened in Excel.
10. Add a separate report for each subject.

These are ideas for a later version. They are not part of this project.

---

## 15. Conclusion

The Student Management System demonstrates how arrays, strings, loops, conditions and functions can work together in one complete C program. It allows a user to add up to 50 students, display them in a table, search by roll number and sort them by total marks. Every value is checked before it is stored, and the total, average and grade are calculated automatically.

The project is intentionally small. The aim was not to use advanced features, but to write a working program where every line can be read and explained. The input checks make the program safe to demonstrate in front of faculty, and the function-wise structure makes the code easy to extend later.

---

## 16. Testing Done

The final program was compiled with GCC and checked with these flags:

```bash
gcc main.c -o sms.exe -Wall -Wextra -Wpedantic -std=c11
```

It also compiled without warnings with `-Wshadow`, `-Wformat=2`, `-Wconversion` and `-Wsign-conversion`.

| # | Test case | Result |
|---|-----------|--------|
| 1 | Choose 5 to exit | Pass |
| 2 | Invalid menu choices: `abc`, blank line, `0`, `6`, `-1`, `1.5`, `12abc`, `1000000000` | Error shown, menu repeated |
| 3 | Menu choice with leading and trailing spaces or tabs | Accepted |
| 4 | End of input at the menu | Program closed with a message |
| 5 | Add one valid student | Summary shown correctly |
| 6 | Add 50 students | All 50 accepted |
| 7 | Try to add the 51st student | Rejected with a capacity message |
| 8 | Enter a duplicate roll number | Rejected and the roll number was asked again |
| 9 | Try a duplicate roll number after sorting | Rejected correctly |
| 10 | Roll number `abc`, `0` or `-5` | Rejected |
| 11 | Roll number `1000000000` | Rejected as too large |
| 12 | Roll number `999999999` | Accepted |
| 13 | Roll number `000123` after `123` | Treated as a duplicate |
| 14 | Empty name or only spaces | Rejected |
| 15 | Name with only punctuation, such as `...` | Rejected |
| 16 | Name with exactly 29 characters | Accepted |
| 17 | Name with 30 characters | Rejected |
| 18 | Name line with 500 characters | Rejected safely; the rest of the line was removed |
| 19 | Name with spaces at the beginning and end | Spaces trimmed |
| 20 | Name with dot, apostrophe and hyphen, such as `A. D'Souza-Kumar` | Accepted |
| 21 | Marks `0` and `100` | Accepted |
| 22 | Marks `-1` and `101` | Rejected |
| 23 | Marks `50.5`, `+50` and `50abc` | Rejected |
| 24 | Marks with leading zeroes or tabs, such as `00050` | Accepted as 50 |
| 25 | Grade boundaries: averages 90, 80, 70, 60, 50 and below 50 | A+, A, B, C, D and F |
| 26 | Total 500 with five marks of 100 | Average 100.00 and grade A+ |
| 27 | Display with an empty list | Proper message shown |
| 28 | Table with the longest allowed name and roll number | All rows exactly 79 columns |
| 29 | Search for an existing roll number | Complete details shown |
| 30 | Search for a missing roll number | Not-found message shown |
| 31 | Search with an empty list | Proper message shown |
| 32 | Search with `abc`, `0`, `-7` or a 10-digit number | Rejected and the roll number was asked again |
| 33 | Sort with an empty list | Proper message shown |
| 34 | Sort with one student | "Already sorted" message shown |
| 35 | Sort students with different totals | Descending order correct |
| 36 | Sort students with equal totals | Original order kept |
| 37 | Sort twice in a row | Records stayed correct |
| 38 | Sort the full list of 50 students | Correct order for all 50 |
| 39 | Input with Windows CRLF line endings | Accepted |
| 40 | Input without a final newline | Accepted; program closed cleanly at end |
| 41 | Very long line at the menu, name or marks prompt | Rejected safely, no crash |
| 42 | Run the program a second time after adding students | List was empty, as expected |
| 43 | Wrong input followed by a valid input | Program recovered and continued |

All checks passed on the final build.

---

## 17. How to Compile and Run

### Windows (MinGW or GCC)

```bash
gcc main.c -o sms.exe
sms.exe
```

### Linux or macOS

```bash
gcc main.c -o sms
./sms
```

### With all normal warning flags

```bash
gcc main.c -o sms.exe -Wall -Wextra -Wpedantic -std=c11
```

### Code::Blocks

1. Open Code::Blocks and create a new Console Application.
2. Choose C as the language.
3. Replace the generated `main.c` with this project's `main.c`.
4. Press Build and Run.

### A short demo order for the presentation

1. Show the menu.
2. Add two students with clear names.
3. Try one duplicate roll number.
4. Display all students.
5. Search for one existing roll number.
6. Search for a missing roll number.
7. Sort by total marks and show the new order.
8. Exit the program.

The duplicate and invalid-mark messages are quick to demonstrate and show that the program checks its input.
