/*
Installation and running:
  To start with C you need:
    - GCC compiler and mingw32-gcc-g++
    - c/c++ and code runner extensions
    - check "run code in terminal" for user input
  To run code from terminal use: gcc "c.c" -o "c" && ./"c"
  If you are using bash terminal in windows you need to switch the slash like this:
    - in "Preferences: Open Settings (JSON)" update to ""c": "gcc \"$fileName\" -o \"$fileNameWithoutExt\" && ./\"$fileNameWithoutExt\"","
---------------------
A function prototype is a declaration of a function that tells
the compiler about the function’s name, return type,
and parameters before its actual definition
---------------------
lib: <stdio.h> <stdbool.h> <string.h> <math.h>

Meaning of '\0':
-It’s a character constant that represents a byte with value 0.
-It is used as a string terminator in C.
-In ASCII, its value is 0 (different from '0' which has ASCII value 48).
-Used by C functions like printf, strlen, etc., to know where a string ends.
-'\0' is simply the invisible marker that tells C where a string stops.

fgets(name, 25, stdin);            // Reads up to 24 characters (plus '\0') into 'name'
if (name[strlen(name) - 1] == '\n') {
    name[strlen(name) - 1] = '\0'; // Removes the newline character if present
} // If you press Enter, fgets will include the newline ('\n') in the string (unless the input was longer than the buffer).
//strlen(name) gives the length of the string (excluding '\0').
---------------------
asign number variables a value to not get include garbage value 

char name[20];
char name[] = "amine";
printf("%1.f", num);
#include <stdbool.h> // import this lib to declare bool
bool b = true;
printf("%d", b);
---------------------
| Feature              | `fgets`                       | `scanf` (`%s`)             |
| -------------------- | ---------------------------   | -------------------------- |
| Reads spaces?        | ✅ Yes (keeps spaces)         | ❌ Stops at first space     |
| Reads whole line?    | ✅ Yes (until newline/limit)  | ❌ Only one word            |
| Buffer overflow risk | ❌ No (you set max size)      | ⚠️ Yes (if input too long) |
| Newline handling     | Keeps `\n` (you may remove)   | Leaves `\n` in buffer      |
| Format control       | ❌ No                         | ✅ Yes (`%d`, `%f`, etc.)   |

sizeof():
-Evaluated at compile time (in most cases).
-Returns the size in bytes of a type or object
strnlen():
-Evaluated at runtime.
-Counts the number of characters in a string

scanf("%d", &age); // Leaves the newline \n (when you press Enter) in the input buffer.
// if there is another "scanf("%d", &age)" %d automatically skips leading whitespace

while (getchar() != '\n');  //discard everything after the number

fgets(name, sizeof(name), stdin); // Now reads the actual string input (name) without being interrupted by the leftover newline.

char grade = '\0';
int age = 0;
scanf("%d", &age);
scanf(" %c", &grade); //Notice the space before %c.
// That space tells scanf to skip all whitespace (spaces, tabs, newlines) before reading the character.
// So it effectively discards the leftover newline automatically.
---------------------
arrays:
Contiguous memory
No bounds checking
Passing arrays to functions – passes a pointer to the first element, not a copy. 
int arr[5];  // the values will be the leftover from the previous program. C doesn't automatically clear memory from pragrams that used that memory previously
int arr[5] = {0};  // the other values will be 0, if char it will be '\0'
int size = sizeof(numbers) / sizeof(numbers[0]);
scanf("%d", &numbers[1]); // update

int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
---------------------
typedef char String[50];

enum Weekday {
    MON, TUE, WED, THU, FRI, SAT, SUN
};
enum Weekday today = WED; // it work with the switch case
---------------------
struct
strcpy(student.name, "Amine"); // update string inside a struct, with strcpy the address remain the same
---------------------
int age = 25;
int *pAge = &age;

print("%p", &age); // address
print("%p", &pAge); // address

// by default the var is passed be value, use pointer to pass it by reference
aFunc(pAge);
void aFunc(int *age) {
  (*age)++; //age will increment the address, i used prenetsess for  precedence
}
---------------------
Files
---------------------
char *grades = malloc(number * sizeof(char)); // it's an array
// if malloc fail it will return a null

free(grades);
grades = NULL;
---------------------
int *scores = calloc(number, sizeof(int)); // it will put 0 by default not like malloc this is the only difference
---------------------
realloc() ; // dynamic arrays work with it
float *temp = realloc(prices, newNumber * sizeof(float));
if (temp == NULL) {
  print("error");
} else {
  prices = temp;
  temp = NULL;
}
---------------------
// segmentation fault
int *p = NULL;
*p = 10;   // ❌ segfault: NULL is not valid memory
---------------------
*/
