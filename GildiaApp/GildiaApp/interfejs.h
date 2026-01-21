#ifndef INTERFEJS_H
#define INTERFEJS_H
#include "gildia.h"

void przywitanie();
void wyswietlMenu();
int pobierzWybor();

void menuWyszukiwania(Bohater* head);
void menuUsuwania(Bohater** head);
void menuSortowania(Bohater** head);

#endif