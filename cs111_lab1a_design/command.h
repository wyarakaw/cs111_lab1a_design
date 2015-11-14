// UCLA CS 111 Lab 1 command interface

typedef enum { false, true } bool;

typedef struct command *command_t;
typedef struct commandNode *commandNode_t;
typedef struct command_stream *command_stream_t;
typedef struct commandStack *commandStack_t;

struct commandNode{
    command_t cmd;
    commandNode_t next;
    commandNode_t prev;
    int tree_number;
};

struct command_stream {
    //head and tail pointers
    commandNode_t head, tail;
    //just in case we need to look in the middle of the list
    commandNode_t current;
    int num_nodes;
};

/* Create a command stream from LABEL, GETBYTE, and ARG.  A reader of
 the command stream will invoke GETBYTE (ARG) to get the next byte.
 GETBYTE will return the next input byte, or a negative number
 (setting errno) on failure.  */
command_stream_t make_command_stream (int (*getbyte) (void *), void *arg);

/* Read a command from STREAM; return it, or NULL on EOF.  If there is
 an error, report the error and exit instead of returning.  */
command_t read_command_stream (command_stream_t stream);

/* Print a command to stdout, for debugging.  */
void print_command (command_t);

/* Execute a command.  Use "time travel" if the integer flag is
 nonzero.  */
void execute_command (command_t, int);


/* Return the exit status of a command, which must have previously been executed.
 Wait for the command, if it is not already finished.  */
int command_status (command_t);

void free_command(command_t);