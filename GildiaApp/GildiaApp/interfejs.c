#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "interfejs.h"
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
	printf("7. Zapisz zmiany (bez wychodzenia).\n");
	printf("8. Zapisz i wyjdz\n");
	printf("------------------------------------\n");
}

int pobierzWybor() {
	int wybor;

	printf("Twoj wybor: ");
	while (scanf("%d", &wybor) != 1 || wybor < 1 || wybor > 8) {
		printf("Blad! Wybierz opcje 1-8: ");
		while (getchar() != '\n');
	}

	while (getchar() != '\n');

	return wybor;
}
void menuWyszukiwania(Bohater* head) {
	if (head == NULL) {
		printf("Brak danych do przeszukania.\n");
		return;
	}
	int n = -1;
	printf("1. wyszukaj wedlug imienia.\n");
	printf("2. wyszukaj wedlug poziomu.\n");
	printf("Twoj wybor: ");

	n = wczytajLiczbe(1, 2);
	if (n == 1) {
		wyszukajImie(head);
	}
	else if (n == 2) {
		wyszukajPoziom(head);
	}
}

void menuUsuwania(Bohater** head) {
	if (*head == NULL) {
		printf("Brak bohaterow do usuniecia.\n");
		return;
	}
	
	printf("1. Usuwanie pojedynczego bohatera po imienu.\n");
	printf("2. Usuwanie bohaterow pasujacych do kryterium.\n");
	printf("Twoj wybor: ");
	int n = wczytajLiczbe(1, 2);
	if (n == 1) {
		usunBohatera(head);
	}
	else if (n == 2) {
		usunWieluBohaterow(head);
	}
}
void menuSortowania(Bohater** head) {
	if (*head == NULL) {
		printf("Lista jest pusta.\n");
		return;
	}

	printf("Jak chcesz posortowac liste?\n");
	printf("1. Alfabetycznie\n");
	printf("2. Poziomowo\n");
	printf("Twoj wybor: ");
	int opcja = wczytajLiczbe(1, 2);
	sortowanie(head, opcja);
	printf("---> Lista zostala posortowana.\n");

	wyswietlRejestr(*head);
}