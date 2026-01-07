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

	wczytajPlik(&rejestr);

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
				wyswietlRejestr(rejestr);
				break;
			}
			case 3: {
				if (rejestr == NULL) {
					printf("Brak danych do przeszukania.\n");
				}
				else {
					int n = -1;
					printf("1. wyszukaj wedlug imienia.\n");
					printf("2. wyszukaj wedlug poziomu.\n");
					printf("Twoj wybor: ");
					n = wczytajLiczbe(1, 2);
					if (n == 1) {
						wyszukajImie(rejestr);
					}
					else if (n == 2) {
						wyszukajPoziom(rejestr);
					}
				}
				break;
			}
			case 4: {
				modyfikacjaBohatera(rejestr);
				break;
			}
			case 5: {
				if (rejestr == NULL) {
					printf("Brak bohaterow do usuniecia.\n");
				}
				else {
					int n = -1;
					printf("1. Usuwanie pojedynczego bohatera po imienu.\n");
					printf("2. Usuwanie bohaterow pasujacych do kryterium.\n");
					printf("Twoj wybor: ");
					n = wczytajLiczbe(1, 2);
					if (n == 1) {
						usunBohatera(&rejestr);
					}
					else if(n == 2){
						usunWieluBohaterow(&rejestr);
					}
				}
				break;
			}
			case 6: {
				if (rejestr == NULL) {
					printf("Lista jest pusta.\n");
				}
				else {
					int opcja = -1;
					printf("Jak chcesz posortowac liste?\n");
					printf("1. Alfabetycznie\n");
					printf("2. Poziomowo\n");
					printf("Twoj wybor: ");
					opcja = wczytajLiczbe(1, 2);
					sortowanie(&rejestr, opcja);
					wyswietlRejestr(rejestr);
				}
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
