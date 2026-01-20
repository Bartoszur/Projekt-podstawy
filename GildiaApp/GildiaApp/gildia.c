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
					printf("Blad: Taki bohater juz istnieje! Wymysl inne imie.\n");
			}
			else {
					tworzenie = 0;
			}
		}
	}

	printf("Wybierz klase (0-WOJOWNIK, 1-MAG, 2-KAPLAN, 3-LOTR, 4-LOWCA, 5-DRUID): ");
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

void zapiszRejestr(Bohater* head, const char* nazwaPliku) {
	FILE *f = fopen(nazwaPliku, "w");
	if (f == NULL) {
		printf("Blad: Nie udalo sie otworzyc pliku do zapisu!\n");
		return;
	}

	Bohater* current = head;
	while (current != NULL) {
		char imieDoZapisu[100];
		strcpy(imieDoZapisu, current->dane.imie);

		for (int i = 0; imieDoZapisu[i] != '\0'; i++) {
			if (imieDoZapisu[i] == ' ') imieDoZapisu[i] = '_';
		}

		fprintf(f, "%s %d %d %d %d %d\n",
			imieDoZapisu,
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

	printf("\n%-3s | %-25s | %-8s | %-9s | %-6s | %-13s | %-10s\n",
		"Nr.", "Imie Bohatera", "Klasa", "Rasa", "Poziom", "Reputacja", "Status");

	int nr = 1;
	
	while (current != NULL) {
		printf("%-3d | %-25s | %-8s | %-9s | %-6d | %-13s | %-10s\n",
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
	
void wczytajPlik(Bohater** head, const char* nazwaPliku) {
	FILE *f = fopen(nazwaPliku, "r");

	if (f == NULL) {
		return;
	}

	char buforImie[100] = { 0 };
	int bKlasa, bRasa, bPoziom, bReputacja, bStatus;

	while (fscanf(f, "%s %d %d %d %d %d",
		buforImie, &bKlasa, &bRasa, &bPoziom, &bReputacja, &bStatus) == 6) {

		Bohater* nowy = malloc(sizeof(Bohater));

		for (int i = 0; buforImie[i] != '\0'; i++) {
			if (buforImie[i] == '_') buforImie[i] = ' ';
		}

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
	printf("--> Wczytano dane z pliku %s.\n", nazwaPliku);
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
				printf("Wybierz nowa klase (0-WOJOWNIK, 1-MAG, 2-KAPLAN, 3-LOTR, 4-LOWCA, 5-DRUID): ");
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
		if (current->dane.status == NA_MISJI) {
			printf("BLAD: Nie mozna usunac bohatera %s - jest w trakcie misji!\n", current->dane.imie);
			return; 
		}
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

	if (current->dane.status == NA_MISJI) {
		printf("BLAD: Nie mozna usunac bohatera %s - jest w trakcie misji!\n", current->dane.imie);
		return;
	}

	prev->nastepny = current->nastepny;
	
	free(current);

	printf("--> Sukces! Usunieto bohatera: %s\n", szukane);
}

void usunWieluBohaterow(Bohater** head) {
	if (head == NULL || *head == NULL) {
		printf("Lista jest pusta.\n");
		return;
	}

	int opcja, wartosc;
	printf("\n--- USUWANIE BOHATEROW ---\n");
	printf("1. Usun bohaterow o danej KLASIE.\n");
	printf("2. Usun bohaterow o danej RASIE.\n");
	printf("3. Usun bohaterow ponizej danego POZIOMU.\n");
	printf("4. Usun bohaterow ponizej poziomu REPUTACJI.\n");
	printf("5. Usun bohaterow o danym STATUSIE.\n");
	printf("0. - Powrot.\n");
	printf("Wybierz kryterium: ");
	opcja = wczytajLiczbe(0, 5);
	if (opcja == 0) return;

	switch (opcja) {
		case 1: {
			printf("Ktora klase chcesz usunac (0-WOJOWNIK, 1-MAG, 2-KAPLAN, 3-LOTR, 4-LOWCA, 5-DRUID)?: ");
			wartosc = wczytajLiczbe(0, 5);
			break;
		}
		case 2: {
			printf("Ktora rase chcesz usunac (0-CZLOWIEK, 1-ELF, 2-KRASNOLUD, 3-DEMON, 4-ORK):?: ");
			wartosc = wczytajLiczbe(0, 4);
			break;
		}
		case 3: {
			printf("Usunac bohaterow ponizej poziomu: ");
			wartosc = wczytajLiczbe(1, 100);
			break;
		}
		case 4: {
			printf("Usunac bohaterow ponizej reputacji: ");
			wartosc = wczytajLiczbe(-50, 150);
			break;
		}
		case 5: {
			printf("Podaj status do usuniecia (0-AKTYWNY, 1-NA_MISJI, 2-RANNY, 3-ZAGINIONY, 4-ZAWIESZONY): ");
			wartosc = wczytajLiczbe(0, 4);
			break;
		}
	}

	int licznik = 0;

	while (*head != NULL && czySpelniaWarunki(*head, opcja, wartosc)) {
		if ((*head)->dane.status == NA_MISJI) {
			printf("Pominieto: %s (jest na misji, nie mozna usunac).\n", (*head)->dane.imie);
			break;
		}

		Bohater* doUsuniecia = *head;
		*head = (*head)->nastepny;
		free(doUsuniecia);
		licznik++;
	}	

	if (*head == NULL) {
		printf("--> Usunieto %d bohaterow. Lista jest pusta.\n", licznik);
		return;
	}

	Bohater* current = *head;

	while (current->nastepny != NULL) {
		if (czySpelniaWarunki(current->nastepny, opcja, wartosc)) {
			if (current->nastepny->dane.status == NA_MISJI) {
				printf("Pominieto: %s (jest na misji).\n", current->nastepny->dane.imie);
				current = current->nastepny;
			}
			else {
				Bohater* doUsuniecia = current->nastepny;
				current->nastepny = doUsuniecia->nastepny;
				free(doUsuniecia);
				licznik++;
			}
		}
		else {
			current = current->nastepny;
		}
	}
	printf("--> Zakonczono. Usunieto lacznie %d bohaterow.\n", licznik);

}

Bohater* wstawSortowanie(Bohater* headSorted, Bohater* nowy, int opcja) {
	int poczatek = 0;

	if (headSorted == NULL) {
		poczatek = 1;
	}
	else if (opcja == 1) {
		if (strcmp(nowy->dane.imie, headSorted->dane.imie) < 0) {
			poczatek = 1;
		}
	}
	else if (opcja == 2) {
		if (nowy->dane.poziom > headSorted->dane.poziom) {
			poczatek = 1;
		}
	}

	if (poczatek == 1) {
		nowy->nastepny = headSorted;
		return nowy;
	}

	Bohater* current = headSorted;

	while (current->nastepny != NULL) {
		int wstaw = 0;

		if (opcja == 1) {
			if (strcmp(nowy->dane.imie, current->nastepny->dane.imie) < 0) {
				wstaw = 1;
			}
		}
		else if (opcja == 2) {
			if (nowy->dane.poziom > current->nastepny->dane.poziom) {
				wstaw = 1;
			}
		}

		if (wstaw == 1) {
			break;
		}

		current = current->nastepny;
	}

	nowy->nastepny = current->nastepny;
	current->nastepny = nowy;

	return headSorted;
}

void sortowanie(Bohater** headSort, int opcja) {
	Bohater* nieSortowana = *headSort;

	if (nieSortowana == NULL || nieSortowana->nastepny == NULL) {
		printf("Lista nie wymaga sortowania.\n");
		return;
	}

	Bohater* posortowanaLista = NULL;

	while (nieSortowana != NULL) {
		Bohater* next = nieSortowana->nastepny;

		nieSortowana->nastepny = NULL;

		posortowanaLista = wstawSortowanie(posortowanaLista, nieSortowana, opcja);

		nieSortowana = next;
	}

	*headSort = posortowanaLista;

	printf("--> Sortowanie zakonczone sukcesem!\n");
}