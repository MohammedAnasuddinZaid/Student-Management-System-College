# Likely Faculty Viva Questions and Simple Answers

These answers are written in simple first-year language. Learn the idea, not the exact words.

---

### 1. What is your project about?

It is a Student Management System written in C. It stores the name, roll number and marks of five subjects for up to 50 students. The user can add students, display all records, search by roll number and sort the records by total marks. Total marks, average marks and grade are calculated by the program.

---

### 2. Which language and headers did you use?

Only C. I used `stdio.h` for input and output and `string.h` for `strlen()` and `strcpy()`.

---

### 3. Why did you choose C?

C is the language taught in the first year, and the project only needs arrays, loops, conditions and functions. C also runs directly in a terminal without any extra libraries.

---

### 4. How many students can the program store?

50. I used `#define MAX_STUDENTS 50`. If the user tries to add the 51st student, the program prints a capacity message and does not ask for the details.

---

### 5. What is `studentCount`?

It is a global integer that stores how many students are currently in the arrays. It starts at 0, is used as the index for the next student, and is also used to check the 50-student limit.

---

### 6. Why are the student arrays global?

So that every function can use the same data directly. This avoids passing many parameters and avoids using pointer parameters in my own functions.

---

### 7. Which arrays are used?

- `char names[50][30]` stores the names.
- `int rollNumbers[50]` stores the roll numbers.
- `int marks[50][5]` stores five marks for each student.
- `char grades[50][4]` stores grades such as `"A+"` and `"F"`.

---

### 8. Why is `names` a two-dimensional array?

One name is a string, which is already a one-dimensional character array. I need 50 names, so I need an array of 50 strings. The first index selects the student and the second index selects the character.

---

### 9. Why is the grade array size 4?

The longest grade is `"A+"`, which has two visible characters and one hidden null character `'\0'`. That needs 3 bytes. I used 4 to keep one byte extra.

---

### 10. What is a string in C?

A string is a character array that ends with the null character `'\0'`. The null character tells functions like `strlen()` and `printf()` where the string stops.

---

### 11. Why did you use `fgets()` instead of `scanf()`?

`scanf("%s")` stops at a space, so a name like "Anas Zaid" would be read as only "Anas". `scanf("%d")` also stops at the first non-digit and leaves the rest of the line in the buffer. `fgets()` reads the whole line, which is easier to check properly.

---

### 12. What is the input buffer?

It is the temporary memory where the characters typed by the user wait until the program reads them. Leftover characters can affect the next input if they are not removed.

---

### 13. What does `clearInputBuffer()` do?

If a line is longer than 199 characters, `fgets()` fills the input array and leaves the rest of the line in the buffer. `clearInputBuffer()` uses `getchar()` in a loop to throw away those extra characters so that the next prompt starts with a clean buffer.

---

### 14. What does `readInputLine()` do?

It calls `fgets()` to read one line into the global `inputLine` array. It removes the newline and also removes a carriage return from Windows CRLF input. If `fgets()` returns `NULL`, it sets `inputClosed = 1` and returns 0.

---

### 15. What does `readNumber()` do?

It looks at `inputLine` and builds a whole number digit by digit. It skips spaces and extra leading zeroes, checks for overflow, and allows only spaces or tabs after the number. It returns -1 if the line is empty, contains letters, contains a decimal point or has extra characters.

---

### 16. How does it reject an input like `12abc`?

The loop reads `1` and `2` and builds the number 12. The next character is `a`, which is not a digit. After skipping spaces, the program finds that the next character is not `'\0'`, so it returns -1.

---

### 17. What happens if the user enters `1.5` or `+50` for marks?

Both are rejected. The decimal point and the plus sign are not digits, and they are not allowed after the number. The program asks for the same subject again. Marks must be whole numbers from 0 to 100.

---

### 18. How do you stop a very large roll number from overflowing `int`?

Before multiplying the current number by 10, `readNumber()` checks if it is already bigger than `MAX_ROLL / 10`. If it is, the function returns -1 immediately. This prevents the multiplication from crossing the `int` limit.

---

### 19. Why do you skip leading zeroes?

So that `000123` is treated as the number 123, which is the same roll number as `123`. This also prevents a valid number from being rejected just because the user typed extra zeroes.

---

### 20. What happens if the input ends while the program is waiting?

`fgets()` returns `NULL`, so `readInputLine()` sets `inputClosed = 1`. Every input loop checks this flag and stops. The program prints "No more input. Program closed." and returns. It does not keep printing prompts forever.

---

### 21. What happens if the user enters a line longer than 199 characters?

`fgets()` keeps the first 199 characters and leaves the rest. `clearInputBuffer()` removes the rest. Then the value is checked normally. A long name is rejected because it is over 29 characters, and a long number is rejected because it is too large or has extra characters.

---

### 22. Why do you remove spaces from the ends of a name?

Leading spaces would push the name out of its table column, and trailing spaces could make an empty name look valid. Spaces inside the name, such as in "Rahul Kumar", are kept.

---

### 23. Why does the name need at least one letter?

So that inputs like `12345` or `...` are not accepted as a name. A name should have at least one letter.

---

### 24. Why is the maximum name length 29?

`NAME_LENGTH` is 30. One byte is needed for the null character `'\0'`, so 29 characters can be stored. The table also has a 29-character name column.

---

### 25. How do you prevent duplicate roll numbers?

Before adding a student, a `for` loop compares the new roll number with every existing roll number. If a match is found, the program prints a message and asks for another roll number. This is a linear search.

---

### 26. What is linear search and where did you use it?

Linear search checks the elements one by one from the beginning. I used it to find a student by roll number and to check for duplicate roll numbers.

---

### 27. How many comparisons can linear search make here?

At most 50, because there can be at most 50 students. For duplicates, the same limit applies.

---

### 28. How are the marks checked?

Each mark is read with `readNumber()`. If the value is less than 0 or more than 100, the program prints a message and asks for the same subject again. A `while` loop repeats until the mark is valid.

---

### 29. How is the total calculated?

`calculateTotal(index)` uses a `for` loop to add the five marks of that student and returns the sum. The maximum total is 500.

---

### 30. How is the average calculated?

`calculateAverage(index)` converts the total to `float` with `(float)` and divides by `5.0f`. The cast and the decimal literal both make sure the answer keeps its decimal part. For example, 456 divided by 5 gives 91.20.

---

### 31. What would happen if you divided by the integer 5?

The result would be an integer, so the decimal part would be lost. For example, 456 divided by 5 would give 91 instead of 91.20.

---

### 32. Explain the grading logic.

The average is checked from the highest range to the lowest:

- 90 or more: A+
- 80 or more: A
- 70 or more: B
- 60 or more: C
- 50 or more: D
- below 50: F

For example, a total of 449 gives an average of 89.80, so the grade is A, not A+.

---

### 33. Why is the grade calculated again in display and search?

The grade is stored when the student is added, and it also moves during sorting. I recalculate it in display and search so that the grade shown always matches the current marks. The marks do not change in this version, but it keeps the program consistent.

---

### 34. What is bubble sort?

Bubble sort compares two neighbouring students. If the left student has a smaller total, the two students are swapped. After each pass, the largest remaining total moves towards the top. It is not the fastest sort, but it is easy to understand.

---

### 35. Why do you swap all the arrays in bubble sort?

One student's details are spread across the name array, the roll number array, the marks array and the grade array. If I swapped only the totals, the name and marks would belong to the wrong student. Every array must move together.

---

### 36. What happens when two students have the same total?

The comparison uses `<`, not `<=`, so equal totals are not swapped. The students keep the order in which they were added. This is called a stable sort.

---

### 37. How many comparisons can bubble sort make?

For 50 students, the worst case is about 50 × 49 / 2 = 1225 comparisons. That is very small for a computer, so bubble sort is fine for this project.

---

### 38. Why does the sort option display the table immediately?

So the user can see the result without choosing Display again. The sort function calls `displayStudents()` after sorting.

---

### 39. How is the table kept aligned?

I used fixed-width format specifiers:

- `%-9d` for a left-aligned roll number.
- `%-29s` for a left-aligned name.
- `%3d` for each mark.
- `%5d` for the total.
- `%7.2f` for the average.
- `%-5s` for the grade.

`printTableLine()` prints 79 hyphens, which is the same width as the heading and rows.

---

### 40. What happens if the student list is empty?

- Display prints "No students registered yet."
- Search prints the same kind of message.
- Sort prints "Nothing to sort."
- Add still works and creates the first student.

---

### 41. What happens if the user tries to add the 51st student?

`addStudent()` checks `studentCount >= MAX_STUDENTS` before asking for any details. It prints "The list is full" and returns to the menu.

---

### 42. What happens if the menu choice is wrong?

`readNumber()` rejects letters and decimal choices. If the number is outside 1 to 5, the `default` case in the `switch` prints an error message. The `while` loop then shows the menu again.

---

### 43. Did you use pointers or structures?

No. I did not declare any pointer variable, structure, union, linked list or dynamically allocated memory. All data is kept in ordinary global arrays, and all functions use indexes to access them.

---

### 44. But `fgets()` takes an array name. Is that not a pointer?

When an array name is passed to a standard library function, C gives the function the address of the first element. That is how the library function is designed. I did not write any pointer variable or pointer arithmetic in my own code. The project was kept to arrays and indexes, as required.

---

### 45. Are the records saved after the program closes?

No. The arrays are in RAM, so they are lost when the program ends. The next run starts with an empty list. This is a limitation of this beginner version.

---

### 46. How can the records be saved in a future version?

File handling can be added. At the start, the program can read records from a text file using `fopen()` and `fscanf()`. After adding or changing a record, it can write the data back using `fprintf()`. This is not included in the current project.

---

### 47. What is a function prototype?

It is a declaration written before `main()` that tells the compiler the function's return type, name and parameters. It allows `main()` to call functions that are defined later in the file.

---

### 48. What does `void` mean in `void addStudent(void)`?

The first `void` means the function does not return a value. The `void` inside the brackets means the function takes no arguments.

---

### 49. Why is `main()` so short?

`main()` only shows the menu, reads the choice and calls the right function with a `switch`. Keeping the menu separate from the feature code makes the program easier to read and test.

---

### 50. What did you learn from this project?

I learned how arrays, strings, loops, conditions and functions work together in a complete program. I also learned that input validation and testing are important, because a program can fail even when the main logic looks correct. Sorting was the hardest part because all the arrays had to move together.
