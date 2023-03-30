#include <stdio.h>
#include "SafeInput.h"
#include "unistd.h"
#include "functions.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


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

void listCards(const State *state){
    system("cls");
    char key;
    do{
    printf("\nCards currently in the system: \n");
    for(int i = 0; i < state->antal; i++){
        
        printCards(&state->cards[i]);
    }
    GetInput("\nPress any key to go back to meny.\n", &key, 1);
    }while (key == '\n');
}

// void createCard(State *state, const char *number) {
//     char answer[10];
//     state->antal++;
//     if(state->antal == 1)
//         state->cards = (Card *)malloc(1 * sizeof(Card));
//     else
//         state->cards = (Card *)realloc(state->cards, state->antal * sizeof(Card));
//     GetInput("Do you want to give access to this card? Y/N: ", answer, 10);
//     bool access = (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0);
//     inputCard(&state->cards[state->antal-1], number, access);
//     state->cards[state->antal-1].access = access;

    void createCard(State *state, const char *number, bool access) {
    state->antal++;
    if(state->antal == 1)
        state->cards = (Card *)malloc(1 * sizeof(Card));
    else
        state->cards = (Card *)realloc(state->cards, state->antal * sizeof(Card));
    inputCard(&state->cards[state->antal-1], number, access);
    state->cards[state->antal-1].access = access;

    
    
    
}


void inputCard(Card *p, const char *number, bool access){
    strcpy(p->number, number);
    p->access = access;

    time_t rawtime;
    struct tm *info;

    time( &rawtime );

    info = localtime( &rawtime );

    strftime(p->buffer, sizeof(p->buffer),"%x-%I:%M%p", info);
    
}
    

void printCards(const Card *p){
    printf("\n");
    char *access;
    if(p->access == 1){
        
        access = "Access";
        
        printf("Card %s :", p->number);
        green();
        printf(" %s", access);
        reset();
        printf(" : Added to system %s", p->buffer);
        }
    else{
        
        access = "No access";
        printf("Card %s :", p->number);
        red();
        printf(" %s", access);
        reset();
        printf(" : Added to system %s", p->buffer);
    } 
    

}


void cardInSystem(Card *p, State *state){
    char input[10];
    bool found = false;

    bool access = false;
   
    GetInput("Enter card number: ", input, 10);

    for(int i = 0; i < state->antal; i++){
        if(strcmp(input, state->cards[i].number) == 0 ){
            found = true;
            p = &state->cards[i];
            break;
        }   
    }
    if(found){
        char answer[10];
        GetInput("Card is in system, do you want to add or remove access? Y/N: ", answer, 10);
        if(strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0){
            if(p->access == true){
                p->access = false;
                printf("Access has been updated.\n");
                access = "No access";
            }
            else{
                p->access = true;
                printf("Access has been updated.\n");
                access = "Access";
            }
           
        }
        else if(strcmp(answer, "n") == 0 || strcmp(answer, "N") == 0)
            printf("Access has not been updated.\n");
            
        else{
            printf("Not a valid entry!\n");
        }
    }
    else{
        char answer[10];
        GetInput("Card is not in system, do you want to add it? Y/N: ", answer, 10);
        if(strcmp(answer, "y") == 0 || strcmp(answer, "Y") == 0){
            Card newCard;
            strcpy(newCard.number, input);
            GetInput("Do you want to give access to this card? Y/N: ", answer, 10);
            access = (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0);
            inputCard(&newCard, input, p->access);
            createCard(state, input, access);
            access = state->cards[state->antal-1].access;
            printf("Card added to system with %saccess.\n", access ? "" : "No ");
        }
        else if(strcmp(answer, "n") == 0 || strcmp(answer, "N") == 0){
            access = "No access";
            printf("Card has not been added.\n");
        }
        else{
            printf("Not a valid input!\n");
        }
    }
}


void fakeCardTest(Card *p, State *state){
    char input[10];
    bool found = false;
    GetInput("Please scan card to enter or \"x\" to go back to admin: ", input, 10);
    while(input[0] != 'x'){
    for(int i = 0; i < state->antal; i++){
        if(strcmp(input, state->cards[i].number) == 0 ){
        found = true;
        p = &state->cards[i];
        break;
        }
        
    }
    if(found){
        if(p->access == true){
            printf("\nCURRENTLY LAMP IS: GREEN\n\n");
        }
        else{
            printf("\nCURRENTLY LAMP IS: RED\n\n");
        }
    }
    else
    {
        printf("Card is not in system.\n");
    }
    found = false;
    GetInput("Please scan card to enter or \"x\" to go back to admin: ", input, 10);
    
}
}

void addToRegistry(const Card *p) {
    FILE *registry;
    registry = fopen("registry.txt", "a");  // open the file in append mode

    if (registry == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char *access;
    if (p->access == 1) {
        access = "Access";
    }
    else {
        access = "No access";
    }

    // write the card details to the file
    fprintf(registry, "Card %s: %s, Added to system %s\n", p->number, access, p->buffer);

    fclose(registry);  // close the file
}

void readFromFile(State *state, const char *filename) {
    FILE *file;
    char line[256];

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        // parse the line and extract card information
        Card card;
        sscanf(line, "Card %[^:]: %[^,], Added to system %[^\n]", card.number, card.buffer, card.buffer);

        char accessStr[10];
        sscanf(line, "Card %*[^:]: %[^,],", accessStr);
        card.access = (strcmp(accessStr, "Access") == 0);

        // check if the card is already in the state struct
        bool exists = false;
        for (int i = 0; i < state->antal; i++) {
            if (strcmp(state->cards[i].number, card.number) == 0) {
                exists = true;
                break;
            }
        }

        // if the card is not in the state struct, add it
        if (!exists) {
            createCard(state, card.number, card.access);
            inputCard(&state->cards[state->antal-1], card.number, card.access);
            state->cards[state->antal-1].access = card.access;
        }
    }

    fclose(fopen("registry.txt", "w"));
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
