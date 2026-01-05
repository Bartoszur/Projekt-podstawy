#define _CRT_SECURE_NO_WARNINGS
#include "narzedzia.h"
#include "gildia.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int czyPoprawneImie(const char* nazwa) {
	if (nazwa == NULL || strlen(nazwa) < 4) {
		return 0;
	}
	for (int i = 0; nazwa[i] != '\0'; i++) {
		if (!isalpha(nazwa[i]) && nazwa[i] != ' ') {
			return 0;
		}
	}
	return 1;
}

int czyUnikalne(Bohater* head, const char* nazwa) {
	Bohater* current = head;

	while (current != NULL) {
		if(strcmp(current->dane.imie, nazwa) == 0) {
			return 0;
		}
		current = current->nastepny;
	}
	return 1;
}

int wczytajLiczbe(int min, int max) {
	int liczba;

	while (1) {
		if (scanf("%d", &liczba) == 1) {
			if (liczba >= min && (max == -1 || liczba <= max)) {
				while (getchar() != '\n');
				return liczba;
			}
		printf("Blad: Podaj liczbe od %d", min);
		if (max != -1) {
			printf(" do %d", max);
		}
		printf(": ");

		while (getchar() != '\n');
		}
		else {
			printf("Blad! To nie jest liczba. Sprobuj ponownie: ");

			while (getchar() != '\n');
		}
	}
}

const char* ocenReputacje(int punkty) {
	if (punkty <= -20) {
		return "Zloczonyca";
	}
	if (punkty < 20) {
		return "Niebezpieczny";
	}
	if (punkty < 40) {
		return "Podejrzany";
	}
	if (punkty < 60) {
		return "Neutralny";
	}
	if (punkty < 80) {
		return "Przyjazny";
	}
	if (punkty < 120) {
		return "Bohater";
	}
	return "Legenda";
}

int czyPoprawneWyszukanie(const char* tekst) {
	if (tekst == NULL) {
		printf("Prosze wpisac poczatek, badz cale imie: ");
		return 0;
	}
	for (int i = 0; tekst[i] != '\0'; i++) {
		if (!isalpha(tekst[i]) && tekst[i] != ' ') {
			return 0;
		}
	}
	return 1;
}

void wyczyscBufor(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}