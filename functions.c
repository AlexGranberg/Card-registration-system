#include <stdio.h>
#include "SafeInput.h"
#include "unistd.h"
#include "functions.h"
#include <stdlib.h>
#include <time.h>


int choice(){
while(1){
    printf("\n\nAdmin menu\n");
    printf("1. Remote open door\n");
    printf("2. List add cards in system\n");
    printf("3. Add remove access\n");
    printf("4. Exit\n");
    printf("9. FAKE TEST SCAN CARD\n");

    int sel;
    if(GetInputInt("Select choice: ", &sel)) return sel;
}
}

void remoteOpenDoor(){
    printf("\nCURRENTLY LAMP IS: GREEN\n\n");
    sleep(3);
    printf("\nCURRENTLY LAMP IS: RED\n\n");
}

void listCards(const State *state){
    printf("Cards currently in the system: \n");
    for(int i = 0; i < state->antal; i++){
        
        printCards(&state->cards[i]);
        // Card *p = state->cards;
        // Card *toPrint = &p[i];
        // printCards(toPrint);

    }
}

void addRemoveAccess(Card *cards, Card *number){

    // char answer[10];
    // GetInput("Enter card number: ", number, 10);
    // GetInput("Do you want to give access to this card? Y/N", answer, 10);
    //     if(strcmp(choice, "Y" || "y") == 1)
    //         cards->access == 1;

    }

void createCard(State *state){
    state->antal++;
    if(state->antal == 1)
        state->cards = (Card *)malloc(1 * sizeof(Card));
    else
        state->cards = (Card *)realloc(state->cards, state->antal * sizeof(Card));
    inputCard(&state->cards[state->antal-1]);

    
}

void inputCard(Card *p){
    char answer[10];
    GetInput("Enter card number: ", p->number, 10);
    GetInput("Do you want to give access to this card? Y/N", answer, 10);
        if(strcmp(answer, "Y") == 0)
            p->access = 1;
        else if(strcmp(answer, "N") == 0)
            p->access = 0;
        else{
            p->access = 0;
        }
    time_t rawtime;
    struct tm *info;

    time( &rawtime );

    info = localtime( &rawtime );

    strftime(p->buffer,100,"%x-%I:%M%p", info);
    

    
}
    

void printCards(const Card *p){
    printf("\n");
    char *access;
    if(p->access == 1){
    
    access = "Access";
    
    printf("Card: %s", p->number);
    green();
    printf(" %s", access);
    reset();
    printf(" %s", p->buffer);
    }
    else{
        
    access = "No access";
    printf("Card: %s", p->number);
    red();
    printf(" %s", access);
    reset();
    printf(" %s", p->buffer);
    } 
    

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