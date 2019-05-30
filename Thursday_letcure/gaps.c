#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();
    if(pid==0){
        printf("Child!\n");
        exit(3);
    }else
    {
       printf("Parent\n");
       printf("Press RETURN to wait\n");
       getchar();

       wait(NULL);
       printf("Press RETURN to wait\n");
       getchar();
    }
    return 0;
}