#include "stdafx.h"
#include "mydata.h"
#include "myinterface.h"
#include "mymess.h"
#include "mystack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

static char *strMenu[] = {
	"[0] Wyjdz z programu",
	"[1] Dodaj studenta",
	"[2] Usun studenta",
	"[3] Znajdz studenta",
	"[4] Pokaz studenta",
	"[5] Zapis do pliku binarnego",
	"[6] Odczyt z pliku binarnego"
};



void MyInterfaceMenu() {
	int wybor = -1;
	int k = -1,c;
	while (wybor!=0) {
		menu();
		printf("\n==========================\n");
		while (scanf_s("%d", &wybor) <= 0) {
			message(MY_MESS_ZLY_WYBOR);
			while ((c = getchar()) != '\n');
			menu();
			printf("\n==========================\n");
		}
		switch (wybor) {
			case INTERFACE_DODAJ:
				MyInterfaceDodaj();
				break;
			case INTERFACE_USUN:
				MyInterfaceUsun();
				break;
			case INTERFACE_ZNAJDZ:
				MyInterfaceZnajdz();
				break;
			case INTERFACE_POKAZ:
				MyInterfacePokaz();
				break;
			case INTERFACE_ZAPISZ_DO_PLIKU:
				MyInterfaceZapisz();
				break;
			case INTERFACE_ODCZYT_Z_PLIKU:
				MyInterfaceOdczyt();
				break;
			case INTERFACE_KONIEC:
				break;
			default:
				message(MY_MESS_ZLY_WYBOR);
				break;
		}
	}
}

static void MyInterfacePokaz() {
	int wybor = -1;
	int c;
	while (wybor != 0) {
		printf("\n\n[0] Wyjdz\n");
		printf("[1] Pokaz jednego studenta\n");
		printf("[2] Pokaz wszystkich studentow\n");
		printf("\n==========================\n");
		while (scanf_s("%d", &wybor) <= 0) {
			while ((c = getchar()) != '\n');
			printf("\n[0] Wyjdz\n");
			printf("[1] Pokaz jednego studenta\n");
			printf("[2] Pokaz wszystkich studentow\n");
			printf("\n==========================\n");
		}
		switch (wybor) {
		case 1:
			MyInterfacePokazJeden();
			break;
		case 2:
			MyInterfacePokazWszystkich();
			break;
		case 0:
			break;
		default:
			message(MY_MESS_ZLY_WYBOR);
			break;
		}
	}
}
static void MyInterfacePokazJeden() {
	int nr = 0;
	MY_STACK * tmp = (MY_STACK *)MyStackWskaznik(nr);
	if (tmp == NULL)
	{
		message(MY_MESS_BRAK_STOSU);
	}
	else {
			printf("\n======================\n");
			MyDataPokaz(tmp->pData);
			printf("======================\n");
	}
}
static void MyInterfacePokazWszystkich() {
	int nr = 0;
	MY_STACK * tmp = (MY_STACK *)MyStackWskaznik(nr);
	if (tmp == NULL)
	{
		message(MY_MESS_BRAK_STOSU);
	}
	else {
		while (tmp != NULL)
		{
			printf("\n======================\n");
			MyDataPokaz(tmp->pData);
			printf("======================\n");
			nr++;
			tmp = (MY_STACK *)MyStackWskaznik(nr);
		};
	}
}
static void menu() {
	size_t i;
	for (i = 0; i < INTERFACE_TOTAL; i++) {
		printf("%s\n", strMenu[i]);
	}
}
static void MyInterfaceDodaj() {
	int localRok,c;
	char str[512];
	printf("Podaj nazwisko studenta:");
	while ((c = getchar()) != '\n');
	gets_s(str);
	printf("Podaj rok urodzenia studenta: ");
	while (scanf_s("%i", &localRok) <= 0) {
		message(MY_MESS_ZLA_WARTOSC);
		while ((c = getchar()) != '\n');
		printf("Podaj rok urodzenia studenta: ");
	}
	int wybor_kierunek=-1;
	int k = -1;
	printf("Kierunek:(Wprowadz odpowiednia cyfre)\n");
	MyInterfacePokazKierunki();
	k = scanf_s("%d", &wybor_kierunek);
	while (k<=0 || wybor_kierunek<0 || wybor_kierunek>=KIERUNEK_OSTATNI) {
		message(MY_MESS_ZLY_WYBOR);
		while ((c = getchar()) != '\n');
		printf("Kierunek:(Wprowadz odpowiednia cyfre)\n");
		MyInterfacePokazKierunki();
		k = scanf_s("%d", &wybor_kierunek);
	}
	void *pdata = MyDataDodaj(str, localRok, wybor_kierunek);
	if (!pdata) {
		MyStackFree();
		exit(1);
	}
	else {
		if (!MyStackDodaj(pdata)) {
			if (message(MY_MESS_BLAD_DODANIA_DO_STOSU) == MY_DECISION_BREAK) {
				MyStackFree();
			}
		}
	}

}
static void MyInterfacePokazKierunki() {
	int i;
	for (i = 0; i < MyDataIloscKierunkow(); i++) {
		MyDataKierunkuDrukuj(i);
	}
}
static void MyInterfaceUsun() {
	int wybor = -1;
	int c;
	while (wybor !=0) {
		printf("\n\n[0] Wroc do menu\n");
		printf("[1] Usun pierwszego studenta\n");
		printf("[2] Wszystkich studentow\n");
		printf("\n==========================\n");
		while (scanf_s("%d", &wybor) <= 0) {
			while ((c = getchar()) != '\n');
			printf("\n[0] Wroc do menu\n");
			printf("[1] Usun pierwszego studenta\n");
			printf("[2] Wszystkich studentow\n");
			printf("\n==========================\n");
		}
		switch (wybor) {
			case 1:
				MyInterfaceUsunPierwszy();
				break;
			case 2:
				MyInterfaceUsunWszystkich();
				break;
			case 0:
				wybor = 0;
				break;
			default:
				message(MY_MESS_ZLY_WYBOR);
				break;
		}
	}
}
static void MyInterfaceUsunPierwszy() {
	MY_STACK tmp = MyStackUsun();
	if (!tmp.pData) {
		message(MY_MESS_BRAK_STOSU);
	}
	else {
		printf("\nUsunieto:\n");
		printf("======================\n");
		MyDataPokaz(tmp.pData);
		printf("======================\n");
		MyDataFree(tmp.pData);
	}

}
static void MyInterfaceUsunWszystkich() {
	MyStackFree();
	printf("Usutnieto wszystkich studentow\n");
}
void MyInterfaceZnajdz() {
	int wybor = -1;
	int c;
	while (wybor != 0) {
		printf("\n\n[0] Wroc do menu\n");
		printf("[1] Znajdz po nazwisku\n");
		printf("[2] Znajdz po roku urodzenia\n");
		printf("[3] Znajdz po kierunku\n");
		printf("\n==========================\n");
		while (scanf_s("%d", &wybor) <= 0) {
			while ((c = getchar()) != '\n');
			printf("\n[0] Wroc do menu\n");
			printf("[1] Znajdz po nazwisku\n");
			printf("[2] Znajdz po roku urodzenia\n");
			printf("[3] Znajdz po kierunku\n");
			printf("\n==========================\n");
		}
		switch (wybor) {
		case 1:
			MyInterfaceZnajdzNazwisko();
			break;
		case 2:
			MyInterfaceZnajdzRok();
			break;
		case 3:
			MyInterfaceZnajdzKierunek();
			break;
		case 0:
			break;
		default:
			message(MY_MESS_ZLY_WYBOR);
			break;
		}
	}
}
static void MyInterfaceZnajdzNazwisko() {
	char str[512];
	int c;
	printf("Wprowadz nazwisko: ");
	while ((c = getchar()) != '\n');
	gets_s(str);
	MY_STUDENT znajdzhDat;
	memset(&znajdzhDat, 0, sizeof(MY_STUDENT));
	int dlugosc = strlen(str) + 1;
	znajdzhDat.nazwisko = (char *)malloc(dlugosc * sizeof(char));
	if (!znajdzhDat.nazwisko) {
		if (message(MY_MESS_PROBLEM_Z_ALOKACJA) == MY_DECISION_BREAK) {
			return;
		}
	}
	strcpy_s(znajdzhDat.nazwisko, dlugosc, str);
	void * pDat = MyStackSzukaj(&znajdzhDat, MyDataZnajdz, 1);

	if (pDat){
		printf("\n======================\n");
		MyDataPokaz(pDat);
		printf("======================\n");
	}
	else {
		message(MY_MESS_BRAK_STUDENTA);
	}

	while (pDat){
		pDat = MyStackSzukaj(&znajdzhDat, MyDataZnajdz, 0);
		if (pDat){
			printf("\n======================\n");
			MyDataPokaz(pDat);
			printf("======================\n");
		}
	}
	if (znajdzhDat.nazwisko) {
		free(znajdzhDat.nazwisko);
		znajdzhDat.nazwisko = NULL;
	}
}
static void MyInterfaceZnajdzRok() {
	int lRok,c;
	printf("Podaj rok urodzenia: ");
	while (scanf_s("%d", &lRok) <= 0) {
		message(MY_MESS_ZLA_WARTOSC);
		while ((c = getchar()) != '\n');
		printf("Podaj rok urodzenia: ");
	}
	int i = MyStackZnajdz(lRok, MyDataSzukaj);
	if (i == 0) message(MY_MESS_BRAK_STUDENTA);
}
void MyInterfaceZnajdzKierunek() {
	int wybor_kierunek, c,k;
	printf("Kierunek:(Wprowadz odpowiednia cyfre)\n");
	MyInterfacePokazKierunki();
	k = scanf_s("%d", &wybor_kierunek);
	while (k <= 0 || wybor_kierunek<0 || wybor_kierunek >= KIERUNEK_OSTATNI) {
		message(MY_MESS_ZLY_WYBOR);
		while ((c = getchar()) != '\n');
		printf("Kierunek:(Wprowadz odpowiednia cyfre)\n");
		MyInterfacePokazKierunki();
		k = scanf_s("%d", &wybor_kierunek);
	}
	int i = MyStackZnajdz(wybor_kierunek, MyDataSzukajKier);
	if (i == 0) message(MY_MESS_BRAK_STUDENTA);
}
static void MyInterfaceZapisz() {

	size_t number = MyStackZlicz(); // ilosc elementow stosu
	if (number == 0) {
		message(MY_MESS_BRAK_STOSU);
	}
	else {
		MyStackZapisz(MyDataZapisz);
		printf("Pomyslnie zapisano do pliku\n\n");
	}
}
static void MyInterfaceOdczyt() {
	if (!My_StackOdczyt(MyDataDodaj)) {
		message(MY_MESS_PRZERWANO_ODCZYT);
	}
	else {
		printf("Pomyslnie wczytano z pliku\n\n");
	}
}