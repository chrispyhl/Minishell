This project has been created as part of the 42 curriculum by cpohl, craabe.


Minishell
chrispyshell$


Description:
This project’s program aims to imitate the primary functionalities of the Bash shell. Specifically, it is supposed to handle input as close to the original shell behavior as possible in the following regards:
+ prompt display (chrispyshell$ )
+ command history (pressing up and down arrows)
+ single quote (‘) and double quote (“) handling
+ redirection commands (<, >, <<, >>)
+ piping (|)
+ environment variables ($), specifically exit status ($?)
+ signal handling: SIGINT (ctrl+C), EOF (ctrl+D), SIGQUIT (ctrl+\)
+ specific built-in commands (echo, cd, pwd, export, unset, env, exit)
The program is supposed to cause no memory leaks except for those caused by the external readline()-function (see section “Additional Notes” for further information).
Handling in the style of Bash is specifically not required for: 
- open quotes
- command chaining via AND (&&) and OR (||)
- parenthesis (([...])) for priorities 
- wildcards (*)
Note that this project’s code adheres to the limitations of the 42 norm.

Instructions:
To execute the custom shell, open terminal and:
1. navigate to root of project folder
2. enter make to compile
3. run ./minishell
The terminal prompt should change to a teal chrispyshell$, meaning the program has launched and awaits input. Close the shell by entering exit or pressing ctrl+D. 

Resources:
We used the very helpful Notion page of two 42 peer students (dreule, gzovkic1; with their explicit permission) for orientation while starting to work on the project. We primarily adapted their git commit commentary practices and some of their structs into our project.
Regarding use of AI, we mainly worked with Gemini for guidance through this project, which proved to have an enormous scope for our experience level. We strictly forbid Gemini from providing us with completed code and solely asked for guiding instructions2. All the code contained in this project is self-written. Furthermore, Gemini was used to automate minor chores (such as extracting function declarations from a .c-file for use in a header) or to quickly clarify unknown programming-related concepts.
[HIER DEN EDGE CASE TESTER NENNEN?]
[NOCH WAS ANDERES?]

Additional Notes:
Workload split
During conceptualization, the program’s functionality was roughly split into to main parts: the parser and the executor, which dictated our folder structure and division of labor. Craabe handled the logic surrounding the main function and its utility functions as well as the parser functionality. Cpohl handled the garbage collector (see information below) and the executor functionality. Edge case handling was done by both project members, with cpohl stemming the majority of the workload, since most edge cases required adjustments mainly inside the executor functionality.

Garbage Collector
[HAUSTE REIN, SONNENSCHEIN]

Memory Leak Checks via Valgrind 
(TL;DR at the bottom)
The subject states:
	The readline() function may cause memory leaks, but you are not required to fix 	them. However, this does not mean your own code, yes the code you 	wrote, can have 	memory leaks.
To suppress memory leak warnings concerning readline(), create a sub.sub file on root level containing the following lines:

{
    ignore_libreadline_leaks
    Memcheck:Leak
    ...
    obj:*/libreadline.so.*
}

Execute Valgrind in terminal via:

valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=sub.sub ./minishell

In addition to memory leaks, this shows file descriptors that were still open upon program completion. 
Note that (usually) Valgrind presents a verdict after each entered command. Only the result following the final closure of the program is representative of the actual memory and file descriptor management, since prior results include reserved memory that is still needed for later use (such as the list of environmental variables). Only upon closing the program properly are all reserved memory spaces freed as intended.

TL;DR: When testing the program via Valgrind, follow the instructions in bold above and ignore all Valgrind results except for the last one shown after program completion.

[NOCH WAS? SUBJECT SCHLÄGT VOR: usage examples, feature list, technical choices]
