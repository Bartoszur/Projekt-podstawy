#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "gildia.h"
#include "narzedzia.h"
#include "interfejs.h"

int main(int argc, char* argv[]) {

	if (argc < 2) {
		printf("BLAD: Nie podano nazwy pliku bazy danych!\n");
		printf("Uzycie: %s <nazwa_pliku.txt>\n", argv[0]);
		return 1;
	}
	const char* nazwaPliku = argv[1];

	int running = 1;
	int wybor;
	Bohater* rejestr = NULL;

	wczytajPlik(&rejestr, nazwaPliku);

	przywitanie();
	
	while (running) {
		wyswietlMenu();
		wybor = pobierzWybor();

		switch (wybor) {
			case 1: {
				dodajBohatera(&rejestr);
				break;
			}
			case 2: {
				wyswietlRejestr(rejestr);
				break;
			}
			case 3: {
				menuWyszukiwania(rejestr);
				break;
			}
			case 4: {
				modyfikacjaBohatera(rejestr);
				break;
			}
			case 5: {
				menuUsuwania(&rejestr);
				break;
			}
			case 6: {
				menuSortowania(&rejestr);
				break;
			}
			case 7: {
				zapiszRejestr(rejestr, nazwaPliku);
				printf("--> Postepy zapisane w pliku '%s'.\n", nazwaPliku);
				break;
			}
			case 8: {
				zapiszRejestr(rejestr, nazwaPliku);
				printf("Zapisano rejestr do pliku '%s'.\n", nazwaPliku);
				running = 0;
				break;
			}
		}
	}

	zwolnijPamiec(rejestr);
	rejestr = NULL;

	return 0;
}
