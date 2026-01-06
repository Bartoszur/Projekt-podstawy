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

void wyszukajImie(Bohater* head) {
	if (head == NULL) {
		printf("Lista jest pusta.\n");
		return;
	}
	
	char szukane[100];

	printf("Wpisz poczatek imienia bohatera: ");

	if (fgets(szukane, sizeof(szukane), stdin) != NULL) {
		szukane[strcspn(szukane, "\n")] = 0; 
	}

	while (czyPoprawneWyszukanie(szukane) == 0) {
		printf("Prosze wpisac poczatek, badz cale imie bohatera: ");

		if (fgets(szukane, sizeof(szukane), stdin) != NULL) {
			szukane[strcspn(szukane, "\n")] = 0;
		}
	}

	int dlugosc = strlen(szukane);
	int znalezione = 0;

	Bohater* current = head;
	int nr = 1;

	while (current != NULL) {

		if (strncmp(current->dane.imie, szukane, dlugosc) == 0) {
			printf("%d %s\n", nr, current->dane.imie);
			znalezione = 1;
		}
		current = current->nastepny;
		nr++;
	}

	if (znalezione == 0) {
		printf("Brak wynikow dla imienia: %s", szukane);
	}
	
}

void wyszukajPoziom(Bohater* head) {
	if (head == NULL) {
		printf("Lista jest pusta.\n");
		return;
	}

	int szukane;
	printf("Jaki poziom chcesz wyszukac (1-100): ");
	szukane = wczytajLiczbe(0, 100);


	int znalezione = 0;
	Bohater* current = head;
	int nr = 1;

	while (current != NULL) {
		if (current->dane.poziom == szukane) {
			printf("%d %s poziom - %d\n", nr, current->dane.imie, szukane);
			znalezione = 1;
		}
		current = current->nastepny;
		nr++;
	}

	if (znalezione == 0) {
		printf("Brak bohaterow na %d poziomie.\n", szukane);
	}
}

void modyfikacjaBohatera(Bohater* head) {
	if (head == NULL) {
		printf("Lista jest pusta.\n");
		return;
	}

	Bohater* current = head;

	int modyfikacja = 0;

	char szukane[100];
	printf("Podaj pelne imie bohatera do modyfikacji: ");

	if (fgets(szukane, sizeof(szukane), stdin) != NULL) {
		szukane[strcspn(szukane, "\n")] = 0;
	}
	while (czyPoprawneImie(szukane) == 0) {
		printf("Blad! Imie musi miec min. 4 znaki i same litery: ");

		if (fgets(szukane, sizeof(szukane), stdin) != NULL) {
			szukane[strcspn(szukane, "\n")] = 0;
		}
	}

	while (current != NULL) {
		if (strcmp(current->dane.imie, szukane) == 0) {
			modyfikacja = 1;
			break;
		}
		current = current->nastepny;
	}

	if (modyfikacja == 0) {
		printf("Brak bohaterow o podanym imieniu.\n");
		return;
	}

	int edycja = 1;
	int wybor;
	while (edycja) {
		printf("\n--- MODYFIKACJA BOHATERA %s ---\n", current->dane.imie);
		printf("Co chcesz zmienic?\n");
		printf("1. Klase\n");
		printf("2. Rase\n");
		printf("3. Poziom\n");
		printf("4. Reputacja\n");
		printf("5. Status\n");
		printf("0. Zakoncz edycje\n");
		printf("Twoj wybor: ");

		wybor = wczytajLiczbe(0, 5);

		switch (wybor) {
			case 1: {
				printf("Wybierz nowa klase 0-WOJOWNIK\n 1-MAG\n 2-KAPLAN\n 3-LOTR\n 4-LOWCA\n 5-DRUID\n");
				current->dane.klasa = wczytajLiczbe(0, 5);
				printf("---> Zmieniono klase.\n");
				break;
			}
			case 2: {
				printf("Wybierz nowa rase (0-CZLOWIEK, 1-ELF, 2-KRASNOLUD, 3-DEMON, 4-ORK): ");
				current->dane.rasa = wczytajLiczbe(0, 4);
				printf("---> Zmieniono rase.\n");
				break;
			}
			case 3: {
				printf("Podaj nowy poziom (1-100): ");
				current->dane.poziom = wczytajLiczbe(1, 100);
				printf("---> Zmieniono poziom.\n");
				break;
			}
			case 4: {
				printf("Podaj nowe punkty reputacji (-50 do 150): ");
				current->dane.reputacja = wczytajLiczbe(-50, 150);
				printf("---> Zmieniono poziom reputacji.\n");
				break;
			}
			case 5: {
				printf("Podaj nowy status bohatera (0-AKTYWNY, 1-NA MISJI, 2-RANNY, 3-ZAGINIONY, 4-ZAWIESZONY): ");
				current->dane.status = wczytajLiczbe(0, 4);
				printf("---> Zmieniono status bohatera.\n");
				break;
			}
			case 0: {
				printf("Koniec edycji bohatera.\n");
				edycja = 0;
				break;
			}
		}

	}
}

void usunBohatera(Bohater** head) {
	if (head == NULL || *head == NULL) {
		printf("Lista  jest pusta.\n");
		return;
	}

	char szukane[100];
	int zgodne = 0;
	printf("Podaj imie bohatera, ktorego chcesz usunac: ");

	if (fgets(szukane, sizeof(szukane), stdin) != NULL) {
		szukane[strcspn(szukane, "\n")] = 0;
	}
	while (czyPoprawneImie(szukane) == 0) {
		printf("Blad! Imie musi miec min. 4 znaki i same litery: ");
		
		if (fgets(szukane, sizeof(szukane), stdin) != NULL) {
			szukane[strcspn(szukane, "\n")] = 0;
		}
	}

	Bohater* current = *head;
	Bohater* prev = NULL;

	if (strcmp(current->dane.imie, szukane) == 0) {
		*head = current->nastepny;
		free(current);
		printf("--> Usunieto bohatera: %s.\n", szukane);
		return;
	}

	while (current != NULL && strcmp(current->dane.imie, szukane) != 0) {
		prev = current;
		current = current->nastepny;
	}

	if (current == NULL) {
		printf("Podany bohater nie znajduje sie w rejestrze.\n");
		return;
	}

	prev->nastepny = current->nastepny;
	
	free(current);

	printf("--> Sukces! Usunieto bohatera: %s\n", szukane);
}