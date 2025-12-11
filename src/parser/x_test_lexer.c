

#include <stdio.h>
#include "../../includes/parser.h"
// Make sure this path points to your actual header!

/* Temporary helper to print enum names
   (Adjust based on your actual enum values)
*/
const char *get_token_type_name(t_token_type type)
{
    if (type == T_WORD) return "WORD";
    if (type == T_PIPE) return "PIPE";
    if (type == T_REDIR_IN) return "REDIR_IN";
    if (type == T_REDIR_OUT) return "REDIR_OUT";
    if (type == T_REDIR_APP) return "REDIR_APP";
    if (type == T_HEREDOC) return "HEREDOC";
    return "UNKNOWN";
}

void debug_print_list(t_token_list *head)
{
    t_token_list *current = head;
    int i = 0;

    printf("--- TOKEN LIST ---\n");
    while (current)
    {
        printf("Node %d:\n", i);
        printf("  Content: [%s]\n", current->token);
        printf("  Type:    %s\n", get_token_type_name(current->token_type));
        printf("------------------\n");
        current = current->next;
        i++;
    }
    printf("--- END ---\n");
}

int main(int argc, char **argv)
{
    t_token_list *list;

    if (argc != 2)
    {
        printf("Usage: ./test_lexer \"your command string\"\n");
        return (1);
    }

    printf("Input: %s\n", argv[1]);

    // Call your function
    list = lexer(argv[1]);

    if (!list)
        printf("Lexer returned NULL (Error or empty string)\n");
    else
        debug_print_list(list);

    // Note: We are not freeing here because you will implement GC later.
    return (0);
}
