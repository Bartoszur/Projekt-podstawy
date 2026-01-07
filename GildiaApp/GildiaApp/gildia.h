#ifndef GILDIA_H
#define GILDIA_H
#include <stdio.h>
#include <stdlib.h>

typedef enum Klasa {
	WOJOWNIK,
	MAG,
	KAPLAN,
	LOTRZYK,
	LOWCA,
	DRUID
} Klasa;

typedef enum Rasa {
	CZLOWIEK,
	ELF,
	KRASNOLUD,
	DEMON,
	ORK
} Rasa;

typedef enum Status {
	AKTYWNY,
	NA_MISJI,
	RANNY,
	ZAGINIONY,
	ZAWIESZONY
} Status;

typedef struct {
	char imie[100];
	Klasa klasa;
	Rasa rasa;
	int poziom;
	int reputacja;
	Status status;
} DaneBohatera;

typedef struct ElementListy {
	DaneBohatera dane;
	struct ElementListy* nastepny;
} Bohater;

void dodajBohatera(Bohater** head);

void zapiszRejestr(Bohater* head, const char* nazwaPliku);

void wyswietlRejestr(Bohater* head);

void wczytajPlik(Bohater** head, const char* nazwaPliku);

void wyszukajImie(Bohater* head);

void wyszukajPoziom(Bohater* head);

void modyfikacjaBohatera(Bohater* head);

void usunBohatera(Bohater** head);

void usunWieluBohaterow(Bohater** head);

Bohater* wstawSortowanie(Bohater* headSorted, Bohater* nowy, int opcja);

void sortowanie(Bohater** headSort, int opcja);

#endif
