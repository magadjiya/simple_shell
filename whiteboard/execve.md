# execve - executes a program

### Prototype
`int execve(const char *pathname, char *const argv[], char *const envp[]);`

### Header file to include
`<unistd.>`

### Key Description
`execve()` executes the program referred to by `pathname`.  This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.

`pathname` must be either a binary executable, or a script starting
       with a line of the form:

           #!interpreter [optional-arg] 

`argv` is an array of pointers to strings passed to the new program as its command-line arguments.  By convention, the first of these strings (i.e., `argv[0]`) should contain the filename associated with the file being executed.  The `argv` array must be terminated by a NULL pointer.  (Thus, in the new program, `argv[argc]` will be <span style="color: red;">NULL</span>.)

`envp` is an array of pointers to strings, conventionally of the form _key=value_, which are passed as the environment of the new program. The envp array must be terminated by a <span style="color: red;">NULL</span> pointer.

### How does it work
The `execve()` function in Unix-like operating systems is responsible for executing a new program. 
   * **It doesn't search for files itself;**

instead, it relies on the operating system's file search mechanisms to locate the executable file. The search process is as follows:

* **Absolute Path**
    If the provided file path in the `execve()` call is an absolute path (i.e., it starts with a "/", indicating the full path to the executable), then the system directly uses that path to execute the program.
* **Relative Path**
    If the provided file path is a relative path (i.e., it doesn't start with a "/"), the system searches through the directories listed in the `PATH` environment variable.
    The `PATH` variable is a colon-separated list of directories where the system looks for executable files.
    The directories are searched in the order they appear in the `PATH`. The first occurrence of the executable file with the specified name in any of these directories is executed.

* **Current Working Directory:**
    If the executable file is not found in any of the directories in the `PATH`, the system checks the current working directory of the process.
