#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Write a c program that does the following:
// Forks off 2 child processes
// Child process instructions:
//    At the start print its pid
//    Sleep for a random number of seconds in the range [5, 20]
//        Each child should sleep for a (potentially) different amount of seconds
//    At the end print a message that it is finished
// Parent process instructions
//    Before forking, print out some initial message
//    After the fork, wait for any child to finish
//    Once a child has finished, print out the pid of the completed child as well as how many seconds it was asleep for.
//        Do not run any kind of timer, think about how the child could send this information back to the parent.
//    Print a message that the parent is done and then end the program
//        The other child might still be running, that's ok.

int main(){
  srand(time(NULL));
  printf("Hello! This is the parent process (pid: %d)\n", getpid());
  if(!fork() || !fork()){
    srand(getpid()); // should give a different random seed
    // child process goes here
    printf(" Hello! This is a child process (pid: %d)\n", getpid());
    int sleep_time = (rand() % 16) + 5;
    sleep(sleep_time);
    printf(" Child process done after sleeping for %d seconds! (pid %d)\n", sleep_time, getpid());

    return sleep_time; // exit with sleep time (parent can read this)
  }
  // parent process goes here
  int status, child_pid;
  child_pid = wait(&status);
  printf("Hello! This is still the parent (pid: %d)\n", getpid());
  printf("The child (pid: %d) slept for %d seconds!\n", child_pid, WEXITSTATUS(status));
  printf("Now the parent is done.\n");

  return 0;
}
