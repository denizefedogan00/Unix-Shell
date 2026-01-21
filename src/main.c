#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAX_ARGS 64

int main()
{
    char *line = NULL;
    size_t len = 0;
    while (1)
    {
        printf("myshell> ");
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

        printf("Command: %s\n", line);

        char *argv[MAX_ARGS];
        int argc = 0;
        int i = 0;
        while (line[i] != '\0')
        {
            while (line[i] == ' ' || line[i] == '\t')
            {
                i++;
            }
            if (line[i] == "\0")
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
        // Debug argv
        printf("argc: %d\n", argc);
        for (int j = 0; argv[j] != NULL; j++)
        {
            printf("argv[%d] = '%s'\n", j, argv[j]);
        }
    }

    free(line);
    return 0;
}
