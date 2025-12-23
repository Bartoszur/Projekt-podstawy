#ifndef GILDIA_H
#define GILDIA_H
#include <stdio.h>
#include <stdlib.h>

enum Klasa {
	WOJOWNIK,
	MAG,
	KAPLAN,
	LOTRZYK,
	LOWCA,
	DRUID
};

enum Rasa {
	CZLOWIEK,
	ELF,
	KRASNALUD,
	MUTANT,
	ORK
};

enum Status {
	AKTYWNY,
	NA_MISJI,
	RANNY,
	ZAGINIONY,
	ZAWIESZONY
};


struct Bohater {
	char imie[100];
	enum Rasa rasa;
	enum Klasa klasa;
	int poziom;
	int reputacja;
	enum Status status;
	struct Bohater* nastepny;
};

#endif
