#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    char *line = NULL;
    size_t len = 0;
    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        ssize_t nread = getline(&line, &len, stdin);

        if (nread == -1)
        {
            printf("shell exit!");
            break;
        }

        printf("Command: %s", line);
    }

    free(line);
    return 0;
}
