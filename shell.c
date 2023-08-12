#include "shell.h"
void shell_helper(char *input);
int main(void)
{
    bool running = true;
    char input[MAX_INPUT_LENGTH];
	int status;

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
        shell_helper(input);
    }

    return 0;
}

void shell_helper(char *input)
{
	if (input[0] == '\n')
            continue;

        if (_strcmp(input, "exit\n") == 0)
        {
            running = false;
            continue;
        }
		else
		 {
            pid_t pid = fork();
            
            if (pid == -1)
            {
                perror("fork");
                return 1;
            }
            else if (pid == 0)
            {
                if (execlp(input, input, NULL) == -1)
                {
                    perror("execve");
                    return 1;
                }
            }
            else
            {
                waitpid(pid, &status, 0);
            }
        }
}