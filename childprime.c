#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(void){
int pipefds[2];
int num;
int i;
int isprime = 0;

if(pipe(pipefds) == -1)
{
  perror("pipe");
  exit(EXIT_FAILURE);
}

pid_t pid = fork();

if(pid == 0)
{
  void sigint_handler(int sig);
  if(signal(SIGINT,sigint_handler) == SIG_ERR)
  { 
    perror("signal");
    exit(1);
  }

   printf("Enter any number:");
   scanf("%d",&num);

   close(pipefds[0]);
   write(pipefds[1],&num,sizeof(num));
   exit(EXIT_SUCCESS);
}
if (pid>0)
  {
   wait(NULL);
   close(pipefds[1]);
   read(pipefds[0],&num,sizeof(num));

     for (i=2;i<=num/2;++i)
        {
        if(num % i==0){
          isprime =1;
          break;
        }
     }

     if(num==1)
     {
         printf("1 is not a prime number.\n");
     }
     else
     {
       if(isprime==0)
       printf("The number you have enter is %d and it is a prime number.\n",num);
       else
       printf("The number you have enter is %d and it is not a prime number.\n",num);
     }

     close(pipefds[0]);
}

return EXIT_SUCCESS;

}

void sigint_handler(int sig)
{
printf("Jangan Kacau Saya!!\n");
}
