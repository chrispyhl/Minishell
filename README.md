*This project has been created as part of the 42 curriculum by cpohl, craabe.*


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
To ensure the robustness of chrispyshell, we utilized the minishell_tester from LucasKuhn (https://github.com/LucasKuhn/minishell_tester), alongside custom stress tests. We focused heavily on:
	File Descriptor Management: Ensuring all pipes and redirections are closed even during execution failures or early exits.
	Signal Consistency: Verifying that the parent shell remains responsive after child processes are terminated by signals.
	Deep Piping: Testing long chains of commands to verify that the recursion/looping in handle_piped_cmd does not exceed system limits.
[NOCH WAS ANDERES?]

Additional Notes:
Workload split
During conceptualization, the program’s functionality was roughly split into to main parts: the parser and the executor, which dictated our folder structure and division of labor. Craabe handled the logic surrounding the main function and its utility functions as well as the parser functionality. Cpohl handled the garbage collector (see information below) and the executor functionality. Edge case handling was done by both project members, with cpohl stemming the majority of the workload, since most edge cases required adjustments mainly inside the executor functionality.

Garbage Collector
To ensure absolute memory stability and strictly adhere to the 42 curriculum's requirements, we implemented a custom Garbage Collector. Instead of manual free management for every temporary string, every allocation is tracked within a centralized linked-list structure using "ft_malloc". This architecture allows us to perform a comprehensive cleanup at the end of each command execution loop by simply calling gc_free, or upon program exit by calling clean_up, effectively preventing memory leaks in complex execution paths. We would like to credit dreule and gzovkic1 for their conceptual guidance and inspiration regarding this implementation.

Memory Leak Checks via Valgrind
(TL;DR at the bottom)
The subject states:
	The readline() function may cause memory leaks, but you are not required to fix them. However, this does not mean your own code, yes the code you wrote, can have memory leaks.

[!] To suppress memory leak warnings concerning readline(), create a sub.sub file on root level containing the following lines:
{
    ignore_libreadline_leaks
    Memcheck:Leak
    ...
    obj:*/libreadline.so.*
}

[!] Execute Valgrind in terminal via:
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=sub.sub ./minishell

In addition to memory leaks, this shows file descriptors that were still open upon program completion.
Note that (usually) Valgrind presents a verdict after each entered command. Only the result following the final closure of the program is representative of the actual memory and file descriptor management, since prior results include reserved memory that is still needed for later use (such as the list of environmental variables). Only upon closing the program properly are all reserved memory spaces freed as intended.

TL;DR: When testing the program via Valgrind, follow the two instructions marked with [!] above and ignore all Valgrind results except for the last one shown after program completion.

[NOCH WAS? SUBJECT SCHLÄGT VOR: usage examples, feature list, technical choices]

Technical Choices:
Heredoc Pre-Processing
A significant architectural decision was to handle all Heredocs before initiating the command execution pipeline. We collect all required inputs in the parent process, storing the resulting file descriptors directly within the command nodes. This prevents terminal conflicts during piped execution and ensures that signal handling (e.g., Ctrl+C to cancel a heredoc) remains stable and predictable.

