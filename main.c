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
Card card;

readFromFile(&state, "registry.txt");

while(1){
    int sel = choice();
    if(sel == 1) remoteOpenDoor();
    if(sel == 2) listCards(&state);
    if(sel == 3) cardInSystem(&card, &state);
    if(sel == 4){
        for (int i = 0; i < state.antal; i++){
        addToRegistry(&state.cards[i]);
        }
        break;
    } 
    if(sel == 9) fakeCardTest(&card, &state);
}

return 0;


}

