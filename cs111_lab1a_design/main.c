#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>
//#include <error.h> UNCOMMENT
#include <string.h>

#include "command-internals.h"
#include "command.h"
#include "alloc.h"

static int
get_next_byte (void *stream)
{
    return getc (stream);
}


static char const *program_name;
static char const *script_name;


int main (int argc, char **argv) {
    
    
    /* char *a[] = {"cat2", "a.txt", NULL};
     
     execvp(a[0], a);
     printf("Hi");
     return 0;
     
     */
    
    int command_number = 1;
    int print_tree = 1;
    int time_travel = 0;
    program_name = argv[0];
    /*
     for (;;)
     switch (getopt (argc, argv, "pt"))
     {
     case 'p': print_tree = 1; break;
     case 't': time_travel = 1; break;
     default: break;
     case -1: goto options_exhausted;
     }
     options_exhausted:;
     */
    script_name = argv[optind];
    FILE *script_stream = fopen (script_name, "r");
    if (! script_stream)
        fprintf(stderr, "%s: cannot open", script_name);
    command_stream_t command_stream =
    make_command_stream (get_next_byte, script_stream);
    
    command_t last_command = NULL;
    command_t command;
    
    
    while ((command = read_command_stream (command_stream)))
    {
        //printf ("# %d\n", command_number++);
        print_command (command);
        
        //free_command(command);
        execute_command(command, 0);
        
    }
    
    /*
     char testCommand[] = "cat -a b<foo.txt>foo2.txt";
     command_t test = createCommand(SIMPLE_COMMAND, testCommand);
     for (int i = 0; test->u.word[i] != '\0'; i++ ){
     for (int j = 0; test->u.word[i][j] != '\0'; j++) {
     printf("%c", test->u.word[i][j]);
     }
     printf("\n");
     }*/
    
    
    return 0;
}

/*
 ORIGINAL MAIN.C
 
 // UCLA CS 111 Lab 1 main program
 
 #include <errno.h>
 #include <error.h>
 #include <getopt.h>
 #include <stdio.h>
 
 #include "command.h"
 
 static char const *program_name;
 static char const *script_name;
 
 static void
 usage (void)
 {
 error (1, 0, "usage: %s [-pt] SCRIPT-FILE", program_name);
 }
 
 static int
 get_next_byte (void *stream)
 {
 return getc (stream);
 }
 
 int
 main (int argc, char **argv)
 {
 int opt;
 int command_number = 1;
 int print_tree = 0;
 int time_travel = 0;
 program_name = argv[0];
 
 for (;;)
 switch (getopt (argc, argv, "pt"))
 {
 case 'p': print_tree = 1; break;
 case 't': time_travel = 1; break;
 default: usage (); break;
 case -1: goto options_exhausted;
 }
 options_exhausted:;
 
 // There must be exactly one file argument.
 if (optind != argc - 1)
 usage ();
 
 script_name = argv[optind];
 FILE *script_stream = fopen (script_name, "r");
 if (! script_stream)
 error (1, errno, "%s: cannot open", script_name);
 command_stream_t command_stream =
 make_command_stream (get_next_byte, script_stream);
 
 command_t last_command = NULL;
 command_t command;
 while ((command = read_command_stream (command_stream)))
 {
 if (print_tree)
	{
 printf ("# %d\n", command_number++);
 print_command (command);
	}
 else
	{
 last_command = command;
 execute_command (command, time_travel);
	}
 }
 
 return print_tree || !last_command ? 0 : command_status (last_command);
 }

*/