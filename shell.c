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

        if (_strcmp(input, "exit\n") == 0)
        {
            running = false;
            continue;
        }
        shell_helper(input);
    }
    return (0);
}
/**
 * shell_helper - function that executes the shell
 * @input: input from the user
 *
 * Return: Always 0.
 */
int shell_helper(char *input)
{
    input[strcspn(input, "\n")] = '\0';  // Remove the trailing newline
    pid_t pid = fork();
    int status;

    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        if (execlp(input, input, NULL) == -1)
        {
            perror("execve");
            return (1);
        }
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return (1);
        }
    }
    return (0);
}