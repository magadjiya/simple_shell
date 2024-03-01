## Task 1
* Handled whitespaces -> created a function to handle white spaces
* Handled error printing to stderr not stdout i.e used `fprintf` instead of `printf`
* Fixed memory leaks specifically `Invalid free()`
* Included the `isNewline()`, `isShellbuiltin()` functions to the non-interactive mode


## Task 4
* Handle wrong `status` format
* Handle exiting with `status` of the last command instead of `EXIT_SUCCESS`



