##Task 2

cisfun $: ls -l

n = getline(line) in the line variable as --> "ls -l\n"

1. Use the variable that stores the no of bytes that getline returns to access and change the the '\n' to '\0'.
2. "ls -l\n" --> "ls -l\0" - null byte ignored

execve x linked list
1. Pass ONLY the cmd (aka user input) from the linked list to execve

## Task 3
__Task Requirements__
- Handle the ``PATH``
- ``fork`` must not be called if the command doesn't exist

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
The two commands produce thesame result. Here's why. 
* `execve()` can successfully execute the command `/bin/ls` togther with the flag `-l` without checking if that file is exists.
* However `execve()` cannot successfully execte the `ls` command because it is not a valid command. To Although `ls` is a tracked alias for `/bin/ls` the pr
