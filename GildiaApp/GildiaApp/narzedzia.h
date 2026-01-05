#ifndef NARZEDZIA_H
#define NARZEDZIA_H

typedef struct ElementListy Bohater;

int czyPoprawneImie(const char* nazwa);

int czyUnikalne(Bohater* head, const char* nazwa);

int wczytajLiczbe(int min, int max);

const char* ocenReputacje(int punkty);

int czyPoprawneWyszukanie(const char* tekst);

#endif