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
void red(); 
void green();
void reset();

void listCards(const State *state);
void printCards(const Card *p);
void createCard(State *state, const char *number, bool access);
void inputCard(Card *p, const char *number, bool access);
void cardInSystem(Card *p, State *state);
void fakeCardTest(Card *p, State *state);

void addToRegistry(const Card *p);
void readFromFile(State *state, const char *filename);
void createCardFromFile(State *state, const char *number, bool access, const char *buffer);
void inputCardFromFile(Card *p, const char *number, bool access, const char *buffer);


#endif
