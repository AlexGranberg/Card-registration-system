#include <stdio.h>
#include "SafeInput.h"


int choice(){
while(1){
    printf("Admin menu\n");
    printf("1. Remote open door\n");
    printf("2. List add cards in system\n");
    printf("3. Add remove access\n");
    printf("4. Exit\n");
    printf("9. FAKE TEST SCAN CARD\n");

    int sel;
    if(GetInputInt("Select choice: ", &sel)) return sel;
}
}