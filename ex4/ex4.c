// Write a program that calls `fork()` and then calls some form of `exec()`
// to run the program `/bin/ls`. Try a few variants of `exec()`, such as 
// `execl()`, `execle()`, `execv()`, and others. Why do you think there 
// are so many variants of the same basic call?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int rc = fork();
    // Your code here
    if(rc < 0) {    // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {    // child process satisfies this branch
        // printf("hello, child here (pid: %d) \n", (int) getpid());
        // execle("/bin/ls", NULL);
        // execl("/bin/ls", "ls", "-l" (char *) NULL);
        // execl("/bin/ls", "ls", "-l" (char *) NULL);
        // execv("/bin/ls", NULL);

        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
    } else {
        int wc = waitpid(rc, NULL, 0);    // `waitpid` call added here
        printf("hello, parent here (pid: %d) of child %d\n", (int) getpid(), rc);
    }
    // Your code here    

    return 0;
}
