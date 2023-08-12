#include "shell.h"

int main(void)
{
    bool running = true;
    char input[MAX_INPUT_LENGTH];
    
    while (running)
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "#shell_dial_sb3$ ", 17);
        else
            running = false;

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            break;
        }
        
        if (input[0] == '\n')
            continue;
        
        if (_strcmp(input, "exit\n") == 0)
        {
            running = false;
            continue;
        }
    }
    
    return 0;
}
