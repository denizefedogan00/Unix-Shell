#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char *line = NULL;
    size_t len = 0;
    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        long nread = getline(&line, &len, stdin);

        if (nread == -1)
        {
            printf("shell exit!");
            break;
        }
    }

    free(line);
    return 0;
}
