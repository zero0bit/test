/*
    This program initially detects the operating system, then displays the running processes according
    to the operating system, and then by entering the PID number of each process, it can be terminated.
*/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*
       pid = Process number
       command = An array of type string that is filled using the PID taken from the input
       and is used to kill each process using the specified command.
    */
    int pid;
    char command[100];

    // The main program's starting loop.
    while (1)
    {
// start if
#ifdef _WIN32 // Detecting the Windows operating system type.
        printf("%s", "OS: Windows.\n");
        system("tasklist");
        printf("%s", "Enter PID to kill (0 : Refresh, -1 : Exit): ");
        scanf("%d", &pid);
        sprintf(command, "taskkill /PID %d /F", pid);

#elif __linux__ // Detecting the Linux operating system type.
        printf("%s", "OS: Linux.\n");
        system("sudo ps -ejH");
        printf("%s", "Enter PID to kill (0 : Refresh, -1 : Exit): ");
        scanf("%d", &pid);
        sprintf(command, "sudo kill -9 %d", pid);

#else // Unknown operating system.
        printf("OS: Unknown");

#endif // End of if

        // Condition for refreshed processes.
        if (pid == 0)
            continue;
        else if (pid == -1) // // Condition for End Program.
            break;

        system(command); // Command to kill any process.

        char ans; // ans = Variable to determine whether the program continues.
        printf("%s", "\nDo you want to continue?(y/n)");
        scanf(" %c", &ans); // scan ans.
        // Condition to check variable to continue program.
        if (ans == 'y')
            continue;
        else
            break;
    }
    return 0;
}
