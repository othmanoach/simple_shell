#include "shell.h"

char *trim(char *str);
void execute_command(char *command);

int main(void)
{
    bool running = true;
    char input[MAX_INPUT_LENGTH];
    char *command;

    while (running)
    {
        if (isatty(STDIN_FILENO))
            _puts("#shell_dial_sb3$ ");
        else
            running = false;

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            if (isatty(STDIN_FILENO))
                _puts("\n");
            break;
        }
        if (input[0] == '\n')
            continue;

        if (_strcmp(input, "exit\n") == 0)
        {
            running = false;
            continue;
        }

        command = strtok(input, "\n");
        while (command != NULL)
        {
            if (command[0] != '\0')
            {
                char *trimmed_command = trim(command);
                if (strlen(trimmed_command) > 0)
                {
                    execute_command(trimmed_command);
                }
            }
            command = strtok(NULL, "\n");
        }
    }
    return (0);
}

void execute_command(char *command)
{
    char *args[MAX_INPUT_LENGTH];
    char *token;
    int i = 0;
	int j = 0;
    int count = 0;

    token = strtok(command, " \n");
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " \n");
        count++;
    }
    args[i] = NULL;

    while (j < count)
    {
        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            return;
        }

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
        j++;
    }
}



char *trim(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    end[1] = '\0';
    return str;
}