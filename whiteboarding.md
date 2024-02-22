## Task 2

cisfun $: ls -l

n = getline(line) in the line variable as --> "ls -l\n"

1. Use the variable that stores the no of bytes that getline returns to access and change the the '\n' to '\0'.
2. "ls -l\n" --> "ls -l\0" - null byte ignored

execve x linked list
1. Pass ONLY the cmd (aka user input) from the linked list to execve

## Task 3
__Task Requirements__
- Handle the ``PATH``


``PATH``
The ``PATH`` is an environment variable available to the process running the ``.\sh`` program that contains a colon-separated list of directories where the system looks for executable files.
The directories are searched in the order they appear in the PATH. The first occurrence of the executable file with the specified name in any of these directories is executed.

```shell
danlinux@CD_BERTHRAN:~/ALX/simple_shell$ ./shell
$ /bin/ls -l 
AUTHORS    exec_multiple_cmds.c  whiteboarding.md
README.md
$ ls -l
AUTHORS    exec_multiple_cmds.c  whiteboarding.md
README.md
```
The two commands produce thesame result because
* `execve()` can successfully execute the command `/bin/ls` togther with the flag `-l` because using the absolute path the OS can locate the executable file. 
* However it cannot successfully execute the `ls` command because its not an absolute path, a relative path or in the current working directory.

In such a case, the program has to perform a search of the directories in the `PATH` variable to determine if the file `\ls` exists. 

- ``fork`` must not be called if the command doesn't exist

If the search is successful, only then can a child process be created using `fork()` to execute the command and it's arguments using `execve()`. I

If the search is successful, a child process should not be created neither should `execve()` be called to execute the file.
