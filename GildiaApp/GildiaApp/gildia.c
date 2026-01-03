#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gildia.h"
#include "narzedzia.h"

void dodajBohatera(Bohater** head) {
	if (head == NULL) {
		printf("Blad krytyczny: Nieprawidlowy wskaznik listy!\n");
		return;
	}

	Bohater* nowy = malloc(sizeof(Bohater));
	int tworzenie = 1;
	
	if (nowy == NULL) {
		return;
	}

	while (tworzenie) {
		printf("\n--- TWORZENIE NOWEGO BOHATERA ---\n");

		printf("Podaj imie bohatera (tylko litery, min. 4 znaki): ");

		if (fgets(nowy->dane.imie, sizeof(nowy->dane.imie), stdin) != NULL) {

			nowy->dane.imie[strcspn(nowy->dane.imie, "\n")] = 0;

			if (czyPoprawneImie(nowy->dane.imie) == 1) {
				tworzenie = 0;
			}
			else {
				printf("Blad! Imie musi miec min. 4 znaki i same litery.\n");
			}
		}
	}

	printf("Wybierz klase (0-WOJ, 1-MAG, 2-KAPLAN, 3-LOTR, 4-LOW, 5-DRUID): ");
	nowy->dane.klasa = (Klasa)wczytajLiczbe(0, 5);

	printf("Wybierz rase (0-CZLOWIEK, 1-ELF, 2-KRASNOLUD, 3-MUTANT, 4-ORK): ");
	nowy->dane.rasa = (Rasa)wczytajLiczbe(0, 4);

	nowy->dane.poziom = 1;
	nowy->dane.reputacja = 50;
	nowy->dane.status = AKTYWNY;

	nowy->nastepny = *head;
	*head = nowy;

	printf("--> Sukces! Bohater %s stworzony.\n", nowy->dane.imie);
}

void zapiszRejestr(Bohater* head) {
	FILE *f = fopen("rejestr.txt", "w");
	if (f == NULL) {
		printf("Blad: Nie udalo sie otworzyc pliku do zapisu!\n");
		return -1;
	}
	Bohater* current = head;
	while (current != NULL) {
		fprintf(f, "%s %d %d %d %d %d\n",
			current->dane.imie,
			current->dane.klasa,
			current->dane.rasa,
			current->dane.poziom,
			current->dane.reputacja,
			current->dane.status);

		current = current->nastepny;
	}

	fclose(f);
}