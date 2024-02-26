## Breakdown of dynamic memory allocation in the shell program

### Case 1: EOF [3 allocations]
- `shell.c`
	- `fprintf()`, `line` & `printf()`. `fprint(f)` and `printf()` frees on return while `line` has to be freed by `free(line)`.
	- No matter the number of printf`()` function calls, memory allocation is counted as 1.

### Case 2: '\n' + EOF [3 allocations]
- `shell.c`
        - `fprintf()`, `line` & `printf()`. `fprint(f)` and `printf()` frees on return while `line` has to be freed by `free(line)`.

### Case 3: exit [4 allocations]
- `shell.c`
	- `fprintf()`, `line` & `printf()`. `fprint(f)` and `printf()` frees on return. 
- `exit_shell.c`
	- `strdup()`. `line` from `shell.c` is passed to `exit_shell()`. So, the duplicated `line` has to be freed from within the `exit_shell()` function only if the _exit_ command was found. `linecp` has to be freed whether or not the _exit_ command was found.


### Case 4: env + EOF [5 allocations]
- `shell.c`
        - `fprintf()`, `line` & `printf()`. `fprint(f)` and `printf()` frees on return.
- `exit_shell.c`
        - `strdup()`. `line` from `shell.c` is passed to `exit_shell()`. So, the duplicated `line` has to be freed from within the `exit_shell()` function only if the _exit_ command was found. `linecp` has to be freed whether or not the _exit_ command was found.
- `env_for_task5.c`
	- `strdup()`. `line`. It has to be free whether or not the _env_ command was found.


### Case 5: valid command + EOF [3 + 21 + allocations]
- `shell.c`
        - `fprintf()`, `line` & `printf()`. `fprint(f)` and `printf()` frees on return.
- `exit_shell.c`
        - `strdup()`. `line` from `shell.c` is passed to `exit_shell()`. So, the duplicated `line` has to be freed from within the `exit_shell()` function only if the _exit_ command was found. `linecp` has to be freed whether or not the _exit_ command was found.
- `env_for_task5.c`
        - `strdup()`. `line`. It has to be free whether or not the _env_ command was found.
- `mulargs_for_task2` - 
	* `strdup()`
	* `malloc()`
	* `realloc` - once the array malloc'd by realloc is freed, this section is taken care of
- `execve_for_task3`
	- `path_linked_list.c` - 
	* `makePathList() -> `add_dir_end():` `malloc()`*21;the linked list has to be freed.
	* `absPath()` - `malloc()` -> `fullPath` -> `filePath`. So filePath must be freed
	- In the event of failed execution within processCmds(), the `cmdline` must also be freed

**NOTES**
1. `strtok(), strncmp()`, getenv(),  NO MALLOC
2. In interactive mode, each time the `while` loop in `shell.c file ` runs, a +1 count of malloc is done for running the `exit_shell()` function and another +1 count for calling the `printenv()` function (provided the _exit_ command isn't passed).

