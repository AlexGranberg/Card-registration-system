#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

typedef struct {
bool access;
char number[10];
char buffer[256];

} Card;

typedef struct {
    Card *cards;
    int antal;

} State;


int choice();
void remoteOpenDoor();
void listCards(const State *state);
void addRemoveAccess(Card *cards, Card *number);
void printCards(const Card *p);
void createCard(State *state, const char *number);

// void createCard(State *state, Card *card);

void inputCard(Card *p, const char *number, bool access);
void cardInSystem(Card *p, State *state);
void fakeCardTest(Card *p, State *state);


void red(); 
void green();
void reset();

#endif