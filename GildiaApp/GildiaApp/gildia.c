#define _CRT_SECURE_NO_WARNINGS
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

				if (czyPoprawneImie(nowy->dane.imie) == 0) {
					printf("Blad! Imie musi miec min. 4 znaki i same litery.\n");
				}
				else if(czyUnikalne(*head, nowy->dane.imie) == 0){
					printf("Blad: Taki bohater juz istnieje! Wymyœl inne imie.\n");
				}
				else {
					tworzenie = 0;
				}
			}
		}

	printf("Wybierz klase 0-WOJOWNIK\n 1-MAG\n 2-KAPLAN\n 3-LOTR\n 4-LOWCA\n 5-DRUID\n: ");
	nowy->dane.klasa = (Klasa)wczytajLiczbe(0, 5);
		
	printf("Wybierz rase (0-CZLOWIEK, 1-ELF, 2-KRASNOLUD, 3-DEMON, 4-ORK): ");
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
		return;
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

void wyswietlRejestr(Bohater* head) {
	Bohater* current = head;
	const char* nazwyKlas[] = { "WOJOWNIK", "MAG", "KAPLAN", "LOTRZYK", "LOWCA", "DRUID" };
	const char* nazwyRas[] = { "CZLOWIEK", "ELF", "KRASNOLUD", "DEMON", "ORK" };
	const char* Statusy[] = { "AKTYWNY", "NA_MISJI", "RANNY", "ZAGINIONY", "ZAWIESZONY" };


	if (head == NULL) {
		printf("Rejestr jest pusty!\n");
		return;
	}

	printf("\n%-3s | %-20s | %-8s | %-9s | %-6s | %-10s | %-10s\n",
		"Nr.", "Imie Bohatera", "Klasa", "Rasa", "Poziom", "Reputacja", "Status");

	int nr = 1;
	
	while (current != NULL) {
		printf("%-3d | %-20s | %-8s | %-9s | %-6d | %-10s | %-10s\n",
			nr,
			current->dane.imie,
			nazwyKlas[current->dane.klasa],
			nazwyRas[current->dane.rasa],
			current->dane.poziom,
			ocenReputacje(current->dane.reputacja),
			Statusy[current->dane.status]
			);
		current = current->nastepny;
		nr++;
	}
}
	
void wczytajPlik(Bohater** head) {
	FILE *f = fopen("rejestr.txt", "r");

	if (f == NULL) {
		return;
	}

	char buforImie[100] = { 0 };
	int bKlasa, bRasa, bPoziom, bReputacja, bStatus;

	while (fscanf(f, "%s %d %d %d %d %d",
		buforImie, &bKlasa, &bRasa, &bPoziom, &bReputacja, &bStatus) == 6) {

		Bohater* nowy = malloc(sizeof(Bohater));

		if (nowy == NULL) {
			break;
		}
		strcpy(nowy->dane.imie, buforImie);
		nowy->dane.klasa = (Klasa)bKlasa;
		nowy->dane.rasa = (Rasa)bRasa;
		nowy->dane.poziom = bPoziom;
		nowy->dane.reputacja = bReputacja;
		nowy->dane.status = (Status)bStatus;

		nowy->nastepny = *head;
		*head = nowy;
	}
	fclose(f);
	printf("--> Wczytano dane z pliku 'Rejestr.txt'.\n");
}