#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "gildia.h"
#include "narzedzia.h"

void przywitanie() {
	printf("Witaj w rejestrze Gildii Poszukiwaczy Przygod!\n");
}
void wyswietlMenu() {
	printf("\n---- SYSTEM ZARZADZANIA GILDIA ----\n");
	printf("1. Dodaj nowego bohatera do rejestru.\n");
	printf("2. Wyswietl caly rejestr.\n");
	printf("3. Wyszukaj bohatera w rejestrze.\n");
	printf("4. Modyfikuj dane bohatera.\n");
	printf("5. Usun bohatera z rejestru.\n");
	printf("6. Sortuj rejestr.\n");
	printf("7. Zapisz i wyjdz\n");
	printf("------------------------------------\n");
}

int pobierzWybor() {
	int wybor;

	printf("Twoj wybor: ");
	while (scanf("%d", &wybor) != 1 || wybor < 1 || wybor > 7) {
		printf("Blad! Wybierz opcje 1-7: ");
		while (getchar() != '\n');
	}
	
	while (getchar() != '\n');

	return wybor;
}


int main() {
	int running = 1;
	int wybor;
	Bohater* rejestr = NULL;

	przywitanie();
	
	while (running) {
		wyswietlMenu();
		wybor = pobierzWybor();

		switch (wybor) {
			case 1: {
				printf("dodawanie nowego bohatera...\n");
				dodajBohatera(&rejestr);
				break;
			}
			case 2: {
				printf("wyswietlanie rejestru...\n");
				break;
			}
			case 3: {
				printf("wyszukiwanie...");
				break;
			}
			case 4: {
				printf("Modyfikowanie...");
				break;
			}
			case 5: {
				printf("Usuwanie...");
				break;
			}
			case 6: {
				printf("Sortowanie...");
				break;
			}
			case 7: {
				zapiszRejestr(rejestr);
				printf("Zapisano rejestr...");
				running = 0;
				break;
			}
		}
	}

	return 0;
}
