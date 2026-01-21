#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

int main()
{
    char *line = NULL;
    size_t len = 0;
    while (1)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s>", cwd);
        }
        else
        {
            printf("shell>");
        }
        fflush(stdout);

        ssize_t nread = getline(&line, &len, stdin);
        len = strlen(line);

        if (nread == -1)
        {
            printf("shell exit!\n");
            break;
        }

        if (line[0] == "\0")
            continue;

        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        if (nread == -1 || strcmp(line, "exit") == 0)
        {
            printf("shell exit!\n");
            break;
        }

        char *argv[MAX_ARGS];
        int argc = 0;
        int i = 0;
        while (line[i] != '\0')
        {
            while (line[i] == ' ' || line[i] == '\t')
            {
                i++;
            }
            if (line[i] == '\0')
                break;
            argv[argc++] = &line[i];
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
                i++;

            if (line[i] != '\0')
            {
                line[i] = '\0';
                i++;
            }
        }
        argv[argc] = NULL;
        if (argc == 0)
            continue;

        if (strcmp(argv[0], "cd") == 0)
        {
            const char *path;
            if (argc == 1)
            {
                path = getenv("HOME");
            }
            else
            {
                path = argv[1];
            }

            if (path == NULL || chdir(path) != 0)
            {
                perror("cd");
            }
            continue;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            execvp(argv[0], argv);
            perror("execvp");
            exit(0);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }
        else
        {
            perror("fork");
        }
    }

    free(line);
    return 0;
}
