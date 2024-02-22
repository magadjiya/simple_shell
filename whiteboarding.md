##Task 2

cisfun $: ls -l

n = getline(line) in the line variable as --> "ls -l\n"

1. Use the variable that stores the no of bytes that getline returns to access and change the the '\n' to '\0'.
2. "ls -l\n" --> "ls -l\0" - null byte ignored

execve x linked list
1. Pass ONLY the cmd (aka user input) from the linked list to execve
