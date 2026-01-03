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
	MUTANT,
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
	Rasa rasa;
	Klasa klasa;
	int poziom;
	int reputacja;
	Status status;
} DaneBohatera;

typedef struct ElementListy {
	DaneBohatera dane;
	struct ElementListy* nastepny;
} Bohater;

void dodajBohatera(Bohater** head);

void zapiszRejestr(Bohater* head);


#endif
