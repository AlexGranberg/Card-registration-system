#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

typedef struct {
bool access;
char number[10];
char buffer[100];

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
void createCard(State *state);
void inputCard(Card *p);

void red(); 
void green();
void reset();

#endif