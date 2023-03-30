#include <stdio.h>
#include "SafeInput.h"
#include "unistd.h"
#include "functions.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


void addToRegistry(const Card *p) {
    FILE *registry;
    registry = fopen("registry.txt", "a"); 

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

    fprintf(registry, "Card %s: %s, Added to system %s\n", p->number, access, p->buffer);

    fclose(registry); 
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
        Card card;
        sscanf(line, "Card %[^:]: %[^,], Added to system %[^\n]", card.number, card.buffer, card.buffer);

        char accessStr[10];
        sscanf(line, "Card %*[^:]: %[^,],", accessStr);
        card.access = (strcmp(accessStr, "Access") == 0);

        bool exists = false;
        for (int i = 0; i < state->antal; i++) {
            if (strcmp(state->cards[i].number, card.number) == 0) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            createCardFromFile(state, card.number, card.access, card.buffer);
            inputCardFromFile(&state->cards[state->antal-1], card.number, card.access, card.buffer);
            state->cards[state->antal-1].access = card.access;
        }
    }

    fclose(fopen("registry.txt", "w"));
}

   void createCardFromFile(State *state, const char *number, bool access, const char *buffer) {
    state->antal++;
    if(state->antal == 1)
        state->cards = (Card *)malloc(1 * sizeof(Card));
    else
        state->cards = (Card *)realloc(state->cards, state->antal * sizeof(Card));
    inputCardFromFile(&state->cards[state->antal-1], number, access, buffer);
    state->cards[state->antal-1].access = access;
    
}

void inputCardFromFile(Card *p, const char *number, bool access, const char *buffer){
    strcpy(p->number, number);
    p->access = access;
    strcpy(p->buffer, buffer);
    
}