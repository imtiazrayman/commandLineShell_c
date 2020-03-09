#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

int main() {

  char* space = "\n ";// this is what will be the separator to split the arguments aka the input you put in.
    // space is looking for a skipped line or a space in our input
  
  /*
    for example: if the program runs:
    shell > ls ./sleep top  these are all separated by a space so strtok is going to know a new argument begins when a space is there/

    also
    shell > ls 
            ./sleep
            top             strtok can also recognize its a new argument when there is a new line.  so it works the sae way.

  */

  char* myWord=NULL; // our word we are reciving. 
  char* argv [1000]; // out array which holds our words.
  char buffer[1000]; // our original array which will hold our input, a temporary array for holding input. 
                      // we are going to take buffer and look for a space(which declared above means its a new line)
  int returnValue = 0; // return value

  while (1) {
    printf("Shell> ");
     fgets(buffer, 1000, stdin); // puting our input into buffer, we are using the stdin because we are not reading from a file.
        // we are using 1000 because that is what we have allocated into buffer. 
        int i = 0; // our counter


        for (myWord = strtok(buffer, space); myWord; myWord = strtok(NULL, space)) { //if this was to be removed from the program it would
          //cause a segmentation fault, a segmentation fault is when the user tries to access memory that does not belong to them.
          //
          argv[i] = myWord;
          i++;
          /*
          strtok 
          means string tokenize, so you break the input into tokens. 
          The way how it breaks the string up is it looks for space which in your case is a new line. 
          So it reads in ur input looks for the next line to end so its “input1(skip line)input2(skip line)”. 
          then it takes those inputs and separates them and put them into your array 
          argv[] : so it becomes [0] :input1 , [1]: input2… etc
          */
        }

        argv[i] = NULL; //for exec to run it needs to know when to stop, so every array must have NULL at the end to tell exec when to stop.
        // how do we know i is the end, well once we break out of the for loop, i is the last index therefore we can assign NULL TO it.

        //strcmp means string compare, which means we are looking for the first argument to be exit to break the loop. 
        if(strcmp(argv[0],"exit") == 0) break; //once exit is typed the shell will exit
        //if exit is not typed, then the program will sit there until given a command from the user
        
        pid_t ChildID; // pid_t means process id type and in this case we call it child id 
        ChildID = fork(); //a fork creates a copy, in this case it is creating a copy of the childID.
    if (ChildID >= 0) {  // if pid is >= to 0 it worked and its either a child or parent
      if (ChildID == 0) { // child pid is always 0, for example a child is 0 but a parent can be 13141
        printf("%d",i);

        execvp(argv[0], argv); // what this means is we are taking our first argument , which would be the first thing in our array, and 
        // running the execvp till the end of the array argv, which as we know means null is at the end.
        // so when argv reaches the end it is null so execvp will run till null. 
      }
      else { // the parent pid 
        wait(NULL); // it will wait till the child is null, if you go back to our execvp and why we put a null in aregv at the end,
        // it is pretty much looking for NULL at the end of the execvp
        // which means child finished running.
      }
    }
    else { // pid is negative which means an error
      printf("FAIL \n");
      returnValue = 1; // if there is an erro we return 1 to the while loop which will break the loop
    }
  }
  return(returnValue); // if it is sucessfull return value will still be 0 so the user will be prompted to run the shell again. 
