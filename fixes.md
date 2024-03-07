## Task 1
* Handled whitespaces -> created a function to handle white spaces
* Handled error printing to stderr not stdout i.e used `fprintf` instead of `printf`
* Fixed memory leaks specifically `Invalid free()`
* Included the `isNewline()`, `isShellbuiltin()` functions to the non-interactive mode


## Task 4 & 8
* Handle wrong `status` format
* Handle exiting with `status` of the last command instead of `EXIT_SUCCESS`

## Task 3
* Have to check if pointers path_val, pathValcpy are NULL

## Task 5
* Once task 3 was fixed task 5 was fixed

## Task 9
* The use of envp[] to print environment will cause error because envp[] cannot be updated by setenv() or unsetenv(). `environ` however, is modified by `setenv` and `unsetenv`

## Task 13
* First, the alias builtin is created anew each time the terminal is run. Initially I thought I'd had to get the aliases already defined within the system. Then, I studied how the `bash shell` handles the alias builtin and I learned.
* A linked list of aliases would be needful for easy access, insertion and modification of aliases.
* I had to create a new memory for each alias name and value. Which I had to free.
* I had to create several functions
	* create an array of aliases passed to the command line
	* get the name of an alias
	* check if the value of an alias is also an alias and get the value
	* create new alias and update old ones
	* check if an alias exists
* To ensure I passed all the checks, I had to handle
	* printing all aliases already defined using the command `alias`
	* printing the alias of aliases with a valid name but no value using the command `alias name1 name2 ...`
	* defining a new alias if the alias does not already exist using the command `alias ls_alias=/bin/ls`
	* updating an old alias if the alias already exists using the command `alias ls_alias=/usr/bin/ls`
	* Executing aliases as valid commands 
	* Executing aliases whose values are aliases as valid commands

## Task 10
* Initially I wanted to make use of a linked list to store the `HOME`, `PWD` and `OLDPWD` directories. Then, I discovered that will be too much use of `malloc`. These values are stored in the `envp` array. So, for this task, only one `dynamic memory allocation` was used to duplicate the command line string.
* It was also important to understand how the default `sh` handled the `cd -` command by first printing the `OLDPWD` before changing to it or the `PWD` in the case where the `OLDPWD` is not set
* It was also important to handle the case where some of either of the `HOME` or `OLDPWD` were removed.

## Task 11
* To handle the semi-colon, I had to rethink a portion of my entire program creating an intermediary function to first analyze the commands to determine if they are commands with multiple commands to run independently or singular commands.
* I had to also learn how to not use `strtok` to separate commands based on a character. It requires more lines of code, no malloc, but it works.

## Task 12
* It was quiet easier to handle 12 since it was just like 11
