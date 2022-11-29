#include <unistd.h>

int main(int argc, char* argv[])
{
  if(argc == 1) { 
      printf("Usage: %s exec command \n", argv[0]);
      return 1;    }

  pid_t pid;
  pid = fork();
  
    if(pid == 0)  {
      wait(0);
    }
    
  else if(pid < 0)    {
      perror("error"); // fork error
      return 1;    }
      
  else{
      execvp(argv[1],argv+1); //execvp(path,argv[])
      return 0;
    }
}
