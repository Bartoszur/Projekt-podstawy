#define _CRT_SECURE_NO_WARNINGS
#include "narzedzia.h"
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
