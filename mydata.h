#pragma once

struct MY_STUDENT {
	char *nazwisko;
	int rok_urodzenia;
	enum KIERUNEK_STUDIOW kierunek;
};

enum KIERUNEK_STUDIOW {
	KIERUNEK_INFORMATYKA,
	KIERUNEK_MATEMATYKA,
	KIERUNEK_FIZYKA,
	KIERUNEK_OSTATNI
};

void MyDataFree(void *ptr);
void * MyDataDodaj(char *nazw, int rok, int kierunek_nr);
static void * MyDataInit(char *nazw, int rok, int kierunek_nr);
void MyDataPokaz(void *ptr);
int MyDataZnajdz(void *pCurData, void *pSearchData);
int MyDataZapisz(void *ptr, FILE * plik);
int MyDataSzukaj(void *ptr, int num);
int MyDataSzukajKier(void *ptr, int num);
int MyDataIloscKierunkow();
void MyDataKierunkuDrukuj(int i);