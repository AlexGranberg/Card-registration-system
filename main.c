#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SafeInput.h"
#include <stdbool.h>
#include "functions.h"




int main(){

system("cls");

State state = {NULL,0};

while(1){
    int sel = choice();
    if(sel == 1) remoteOpenDoor();
    if(sel == 2) listCards(&state);
    if(sel == 3) createCard(&state);
    if(sel == 4) break;
}

return 0;


}

