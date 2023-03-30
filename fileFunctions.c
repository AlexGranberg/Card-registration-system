#include <stdio.h>
#include "SafeInput.h"
#include "unistd.h"
#include "functions.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


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

