# Likely Faculty Viva Questions and Simple Answers

These answers are written in simple first-year language. Learn the idea, not the exact words.

---

### 1. What is your project about?

It is a Student Management System. It stores the name, roll number and five subject marks of students and can display them, search for a student by roll number and sort students by total marks.

---

### 2. Which language did you use?

Only C. I used the standard headers `stdio.h` for input/output and `string.h` for string functions.

---

### 3. Why did you use arrays?

Arrays let us store many values of the same type under one name. For example, `rollNumbers[50]` stores 50 roll numbers, and `marks[50][5]` stores five marks for each of 50 students.

---

### 4. What is the maximum number of students? Why?

50. I used the constant `MAX_STUDENTS 50`. If we try to add the 51st student, the program prints a message and does not add the student.

---

### 5. What is `studentCount`?

It is a global integer that keeps the number of students currently stored. It starts at 0. It is used as the index where the next student is stored and also to check whether the arrays are full.

---

### 6. Why are the arrays declared globally?

So that all functions can use the same data directly. This avoids passing many parameters and also avoids using pointers.

---

### 7. What does `#define MAX_STUDENTS 50` do?

It defines a constant named `MAX_STUDENTS` with value 50. Before compilation, the compiler replaces the name with 50. If I want to change the capacity later, I only change this one line.

---

### 8. Why did you use `fgets()` for the name but `scanf()` for numbers?

`scanf("%s")` stops at a space, so a name like "Anas Zaid" would be read as only "Anas". `fgets()` reads the whole line including spaces. Numbers are read with `scanf("%d")`.

---

### 9. What does `clearInputBuffer()` do?

After `scanf()` reads a number, the Enter key (newline) stays in the input buffer. If we call `fgets()` next, it would read that newline as an empty name. `clearInputBuffer()` throws away those leftover characters.

---

### 10. How do you prevent duplicate roll numbers?

Before adding a student, I loop through all existing roll numbers using a `for` loop. If the new roll number matches any existing one, the program prints "Duplicate not allowed" and returns from `addStudent()`.

---

### 11. How do you check that marks are valid?

I use a `do-while` loop. If the marks are less than 0 or more than 100, an error message is printed and the user is asked to enter the marks again.

---

### 12. How is the total calculated?

The function `calculateTotal(index)` uses a `for` loop to add `marks[index][0]` to `marks[index][4]` and returns the sum.

---

### 13. How is the average calculated?

`calculateAverage(index)` calls `calculateTotal(index)` and divides by 5. I write `5.0f` so the answer is a decimal number such as 91.20 instead of 91.

**Follow-up:** What happens if you divide by 5 (integer)?
The answer would be an integer and the decimal part would be lost due to integer division.

---

### 14. Explain the grading logic.

`calculateGrade(index)` finds the average. If it is 90 or more the grade is A+, 80 or more is A, 70 or more is B, 60 or more is C, 50 or more is D, otherwise F. The grade string is stored in `grades[index]`.

---

### 15. Why is the grade array size 4?

A grade like "A+" needs 2 characters plus one hidden null character `'\0'`, so 3 characters are enough. I used 4 to be safe.

---

### 16. What is linear search? Where did you use it?

Linear search means checking elements one by one from the beginning. I used it in `searchStudent()` to find the roll number and also in `addStudent()` to find duplicates.

---

### 17. How many comparisons can linear search do in this program?

At most 50, because there can be a maximum of 50 students.

---

### 18. What is bubble sort?

Bubble sort repeatedly compares two neighbouring elements. If they are in the wrong order, they are swapped. After each pass, one value reaches its correct position. It is slow but very easy to understand.

---

### 19. Why do you swap all the arrays together?

Because one student's data is spread across several arrays: name, roll number, five marks and grade. If we swap only the totals, the marks would belong to the wrong student. Swapping every array keeps each student's details together.

---

### 20. What will happen if the user enters letters instead of a menu choice?

`scanf("%d", &choice)` will fail and return 0. The program prints "Invalid input" and clears the buffer, then shows the menu again.

---

### 21. What is a function prototype?

It is the declaration of a function written before `main()`. It tells the compiler the function name, return type and parameters before the function is actually used.

---

### 22. What does `void` mean in `void addStudent(void)`?

The first `void` means the function does not return any value. The `void` inside brackets means the function takes no arguments.

---

### 23. What are `%-8d` and `%.2f` in `printf()`?

`%-8d` prints an integer in a left-aligned column of width 8. `%.2f` prints a float with exactly two digits after the decimal point. These are used to make the table look neat.

---

### 24. Did you use pointers or structures?

No. The project uses only arrays and simple functions. The requirement was to keep the code understandable for a first-year student.

---

### 25. Are the records saved after the program closes?

No. All data is in arrays in the main memory (RAM), so it is lost when the program exits. This is a limitation of this beginner version.

---

### 26. How can this limitation be removed in future?

By using file handling (`fopen`, `fprintf`, `fscanf`) to write the records to a text file and read them back when the program starts. That can be added as a future enhancement.

---

### 27. Which feature did you find hardest?

Sorting, because five different arrays have to be swapped together. Once I understood bubble sort, it became simple.

---

### 28. What did you learn from this project?

I learned how arrays, loops, conditions and functions work together in a complete program, and how to validate user input and display output in a structured way.
