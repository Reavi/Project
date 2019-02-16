#include "stdafx.h"
#include "mydata.h"
#include "mymess.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma warning (disable : 4996)
static char *kierunkiStudiow[] = {
	"[0]Informatyka",
	"[1]Matematyka",
	"[2]Fizyka"
};
void MyDataKierunkuDrukuj(int i) {
	printf("%s\n", kierunkiStudiow[i]);
}
//Zwolnienie pamiêci
void MyDataFree(void *ptr) {
	MY_STUDENT *pDat = (MY_STUDENT *)ptr;
	if (pDat->nazwisko) {
		//printf("zwalniam pamiec\n");
		free(pDat->nazwisko);
		pDat->nazwisko = NULL;
	}
	if (pDat)
		free(pDat);

}
void * MyDataDodaj(char *nazw, int rok, int kierunek_nr) {
	return MyDataInit(nazw, rok, kierunek_nr);
}
static void * MyDataInit(char *nazw, int rok, int kierunek_nr) {
	KIERUNEK_STUDIOW kierunekLocal;
	switch (kierunek_nr) {
	case KIERUNEK_INFORMATYKA:
		kierunekLocal = KIERUNEK_INFORMATYKA;
		break;
	case KIERUNEK_MATEMATYKA:
		kierunekLocal =KIERUNEK_MATEMATYKA;
		break;
	case KIERUNEK_FIZYKA:
		kierunekLocal =KIERUNEK_FIZYKA;
		break;
	default:
		message(MY_MESS_ZLY_WYBOR);
		break;
	}
	MY_STUDENT *pdat = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));

	if (!pdat) {
		if (message(MY_MESS_PROBLEM_Z_ALOKACJA) == MY_DECISION_BREAK) {
			return NULL;
		}
	}
	pdat->nazwisko = NULL;
	int dlugosc = strlen(nazw) + 1;
	//printf("\nNazwisko dlugosc : %d\n", dlugosc);
	pdat->nazwisko = (char *)malloc(dlugosc * sizeof(char));
	if (!(pdat->nazwisko)) {
		if (message(MY_MESS_PROBLEM_Z_ALOKACJA) == MY_DECISION_BREAK) {
			if (pdat) free(pdat);
			return NULL;
		}
	}
	strcpy_s(pdat->nazwisko, dlugosc,nazw);
	pdat->rok_urodzenia = rok;
	pdat->kierunek = kierunekLocal;

	return (void *)(pdat);
}
int MyDataIloscKierunkow() {
	return KIERUNEK_OSTATNI;
}
void MyDataPokaz(void *ptr) {
	MY_STUDENT*p = (MY_STUDENT *)ptr;
	if (p)
	{
		printf("Nazwisko: %s\n", p->nazwisko);
		printf("Rok urodzenia: %d\n", p->rok_urodzenia);
		switch (p->kierunek) {
		case KIERUNEK_INFORMATYKA:
			printf("Kierunek: INFORMATYKA\n");
			break;
		case KIERUNEK_MATEMATYKA:
			printf("Kierunek: MATEMATYKA\n");
			break;
		case KIERUNEK_FIZYKA:
			printf("Kierunek: FIZYKA\n");
			break;
		default:
			message(MY_MESS_ZLA_WARTOSC);
			break;
		}

	}
}
int MyDataZnajdz(void *pCurData, void *pSearchData){

	MY_STUDENT *pcur = (MY_STUDENT *)pCurData;
	MY_STUDENT *psearch = (MY_STUDENT *)pSearchData;

	if (strcmp(pcur->nazwisko, psearch->nazwisko)== 0)
		return 1;

	return 0;
}

int MyDataZapisz(void *ptr,FILE * plik) {
	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	size_t dlugosc = strlen(tmp->nazwisko) + 1;
	if (fwrite(&dlugosc, sizeof(size_t), 1, plik) < 1) {
			if (message(MY_MESS_PROBLEM_Z_ZAPISEM) == MY_DECISION_BREAK) {
				return 0;
			}
	}
	if (fwrite(tmp->nazwisko, dlugosc, 1, plik) < 1) {
		if (message(MY_MESS_PROBLEM_Z_ZAPISEM) == MY_DECISION_BREAK) {
			return 0;
		}
	}
	if (fwrite(&tmp->rok_urodzenia, sizeof(int), 1, plik) < 1) {
		if (message(MY_MESS_PROBLEM_Z_ZAPISEM) == MY_DECISION_BREAK) {
			return 0;
		}
	}
	if (fwrite(&tmp->kierunek, sizeof(int), 1, plik) < 1) {
		if (message(MY_MESS_PROBLEM_Z_ZAPISEM) == MY_DECISION_BREAK) {
			return 0;
		}
	}
	return 1;
}
int MyDataSzukaj(void *ptr, int num) {
	MY_STUDENT *p = (MY_STUDENT *)ptr;
	if (p->rok_urodzenia == num) {
		printf("\n======================\n");
		MyDataPokaz(ptr);
		printf("======================\n");
		return 1;
	}
	return 0;
}
int MyDataSzukajKier(void *ptr, int num) {
	MY_STUDENT *p = (MY_STUDENT *)ptr;
	if (p->kierunek == num) {
		printf("\n======================\n");
		MyDataPokaz(ptr);
		printf("======================\n");
		return 1;
	}
	return 0;
}