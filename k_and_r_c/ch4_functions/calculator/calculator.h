/* header file for calculator program
 * It declares variables, constants, and functions accessible
 * to other source files compiled together and use this header file
 */

#define NUMBER '0'
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int getop(char []);
