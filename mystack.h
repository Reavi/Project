#pragma once

struct MY_STACK {
	void *pData;				//Wskaünik do danych typu void
	MY_STACK *next;				//Wskaünik do elemntu niøej
};


typedef void (*FreeData)(void *pdat);
typedef int(*ZapiszData)(void *pdat,FILE * plik);
typedef void*(*ZapiszStudent)(char *nazw, int rok, int kierunek_nr);
typedef int (CompData)(void * pcurData, void * pSearchData);
typedef int(*ZnajdzData)(void *pdat, int num);
void MyStackInit(FreeData pFreeDat);
void MyStackFree();
MY_STACK * MyStackDodaj(void *pdat);
MY_STACK MyStackUsun();
void * MyStackSzukaj(void *pSearchDat, CompData ptr_comp_fun, int FirstEntry);
int MyStackZlicz();
void MyStackZapisz(ZapiszData pZapData);
int My_StackOdczyt(ZapiszStudent pZaStu);
void * MyStackWskaznik(int nr);
int MyStackZnajdz(int num,ZnajdzData MyDataSzukaj);
static void file_desc_free(__int64 *file_desc);