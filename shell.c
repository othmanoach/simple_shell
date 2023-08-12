#include "shell.h"

int shell_helper(char *input);

/**
 * main - function that executes the shell
 *
 * Return: Always 0.
 */
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

        if (strcmp(input, "exit\n") == 0)
        {
            running = false;
            continue;
        }
        shell_helper(input);
    }
    return (0);
}

int shell_helper(char *input)
{
    char *args[MAX_INPUT_LENGTH];
    char *token;
    int i = 0;
    pid_t child_pid;

    token = strtok(input, " ");
    
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    child_pid = fork();

    if (child_pid == -1) return (-1);

    if (child_pid == 0)
    {
        execve(args[0], args, NULL);
        perror("shell_dial_sb3");
        exit(1);
    }
    else
    {
        int status;
        waitpid(child_pid, &status, 0);
    }

    return (0);
}