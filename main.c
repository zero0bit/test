#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char command[100];
    int pid;
    while (1)
    {
#ifdef _WIN32
        printf("%s", "OS: Windows.\n");
        system("tasklist");
        printf("%s", "Enter PID to kill (0 : Refresh, -1 : Exit): ");
        scanf("%d", &pid);
        sprintf(command, "taskkill /PID %d /F", pid);

#elif __linux__
        printf("%s", "OS: Linux.\n");
        system("sudo ps -ejH");
        printf("%s", "Enter PID to kill (0 : Refresh, -1 : Exit): ");
        scanf("%d", &pid);
        sprintf(command, "sudo kill -9 %d", pid);

#else
        printf("OS: Unknown");

#endif

        if (pid == 0)
            continue;
        else if (pid == -1)
            break;

        system(command);

        char ans;
        printf("%s", "\nDo you want to continue?(y/n)");
        scanf(" %c", &ans);
        if (ans == 'y')
            continue;
        else
            break;
    }
    return 0;
}