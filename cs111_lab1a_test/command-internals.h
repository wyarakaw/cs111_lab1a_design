// UCLA CS 111 Lab 1 command internals

enum command_type
{
    AND_COMMAND,            // A && B
    SEQUENCE_COMMAND,       // A ; B
    OR_COMMAND,             // A || B
    PIPE_COMMAND,           // A | B
    SIMPLE_COMMAND,         // a simple command
    SUBSHELL_COMMAND,       // ( A )
    SUBSHELL_OPEN,
    SUBSHELL_CLOSED
};

enum input_redirect_type
{
    NONE_INPUT_REDIRECT,
    REGULAR_INPUT_REDIRECT,
    AMPERSAND_INPUT_REDIRECT,       // A <& B
    RW_INPUT_REDIRECT               // A <> B
};

enum output_redirect_type
{
    NONE_OUTPUT_REDIRECT,
    REGULAR_OUTPUT_REDIRECT,
    APPEND_OUTPUT_REDIRECT,         // A >> B
    AMPERSAND_OUTPUT_REDIRECT,      // A >& B
    PIPE_OUTPUT_REDIRECT            // A >| B
};

// Data associated with a command.
struct command
{
    enum command_type type;
    enum input_redirect_type input_type;
    enum output_redirect_type output_type;
    
    // Exit status, or -1 if not known (e.g., because it has not exited yet).
    int status;
    
    // 0 if -C option was not declared, 1 if -C option was declared
    int NO_CLOBBER;
    
    // I/O redirections, or 0 if none.
    char *input;
    char *output;
    
    int tree_number;
    
    
    union
    {
        // for AND_COMMAND, SEQUENCE_COMMAND, OR_COMMAND, PIPE_COMMAND:
        struct command *command[2];
        
        // for SIMPLE_COMMAND:
        char **word;
        
        // for SUBSHELL_COMMAND:
        struct command *subshell_command;
    } u;
};