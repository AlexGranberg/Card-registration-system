#include <stdio.h>
#include "SafeInput.h"
#include "unistd.h"
#include "functions.h"
#include <stdlib.h>


int choice(){
while(1){
    printf("\nAdmin menu\n");
    printf("1. Remote open door\n");
    printf("2. List add cards in system\n");
    printf("3. Add remove access\n");
    printf("4. Exit\n");
    printf("9. FAKE TEST SCAN CARD\n");

    int sel;
    if(GetInputInt("Select choice: ", &sel)) return sel;
    else{
        printf("Not a valid entry!\n");
    }
}
}

void remoteOpenDoor(){
    printf("\nCURRENTLY LAMP IS: GREEN\n\n");
    sleep(3);
    printf("\nCURRENTLY LAMP IS: RED\n\n");
}

void red () {
  printf("\033[1;31m");
}

void green () {
  printf("\033[0;32m");
}

void reset () {
  printf("\033[0m");
}
