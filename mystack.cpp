#include "stdafx.h"
#include "mystack.h"
#include "mymess.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)
static MY_STACK *first = NULL; //WskaŸnik do pierwszego elemenu w STOSIE
FreeData ptr_free_dat;         //Deklaracja wskaznika do funkcji typu FreeData

void MyStackInit(FreeData pFreeDat) {
	first = NULL;
	ptr_free_dat = pFreeDat;
}
void MyStackFree() {
	MY_STACK *p = first, *ptmp = NULL;

	while (p) {
		(*ptr_free_dat)(p->pData);
		ptmp = p;
		p = p->next;
		free(ptmp);
	}
	first = NULL;

}

MY_STACK * MyStackDodaj(void *pdat) {
	MY_STACK *teraz = (MY_STACK *)malloc(sizeof(MY_STACK));
	if (!teraz) {
		if (message(MY_MESS_PROBLEM_Z_ALOKACJA) == MY_DECISION_BREAK) {
			MyStackFree();
			exit(1);
		}
	}
	if (!first) {
		teraz->next = NULL;
	}
	teraz->next=first;
	first = teraz;

	//Ustawiamy pData
	teraz->pData = pdat;

	return first;
}
MY_STACK MyStackUsun() {
	MY_STACK rv;
	if (!first) {
		rv.next = NULL;
		rv.pData = NULL;
	}else {
		MY_STACK * ptmp = first->next;
		rv.pData = first->pData;
		rv.next = NULL;
		free(first);
		first = ptmp;
	}
	return rv;
}
void * MyStackSzukaj(void *pSearchDat, CompData ptr_comp_fun, int FirstEntry) {
	static MY_STACK *p;
	MY_STACK *ptmp = NULL;

	if (FirstEntry)
		p = first;

	while (p){
		if (!(*ptr_comp_fun)(p->pData, pSearchDat)){
			p = p->next;
		}else{
			ptmp = p;
			p = p->next;
			return ptmp->pData;
		}
	}

	return NULL;
}
int MyStackZnajdz(int num, ZnajdzData MyDataSzukaj) {
	MY_STACK *p = first;
	int ilosc = 0;
	if (p == NULL) return ilosc;
	while (p) {
		ilosc += MyDataSzukaj(p->pData, num);
		p = p->next;
	}
	return ilosc;
}
void MyStackZapisz(ZapiszData pZapData) {
	MY_STACK *p = first;
	size_t it, no_items = MyStackZlicz();
	FILE * plik;
	plik = fopen("data.bin", "wb");
	if (!plik) {
		if (message(MY_MESS_PLIK) == MY_DECISION_BREAK) {
			MyStackFree();
			exit(1);
		}
	}
	__int64 *fileDesc = (__int64 *)malloc((no_items + 1) * sizeof(__int64));
	if (!fileDesc) {
		if (message(MY_MESS_PROBLEM_Z_ALOKACJA) == MY_DECISION_BREAK) {
			fclose(plik);
			MyStackFree();
			exit(1);
		}
	}
	//Zapisujemy ilosc elementow stosu
	//printf("Zapis ilosc elementow: %d\n", no_items);
	if (fwrite(&no_items, sizeof(size_t), 1, plik) != 1) {
		if (message(MY_MESS_PROBLEM_Z_ZAPISEM) == MY_DECISION_BREAK) {
			fclose(plik);
			file_desc_free(fileDesc);
			return;
		}
	}
	//Zostawiamy miejsce na pocz¹tku pliku dla fileDesc
	_fseeki64(plik, (no_items + 1) * sizeof(__int64), SEEK_CUR);
	for (it = 0; it < no_items; ++it) {
		//zapisywanie do fileDesc aktualnej pozycji wskaŸnika w pliku
		fileDesc[it] = ftell(plik);
		//Wywolaniu funkcji zapisu studenta
		if (!((*pZapData)(p->pData, plik))) {
			fclose(plik);
			file_desc_free(fileDesc);
			return;
		}
		//przesuniecie wskaznika
		p = p->next;
	}
	//zapisanie ostatniej pozycji wskaznika pliku
	fileDesc[no_items] = ftell(plik);
	//Ustawienie pozycji wskaznika za zapisana iloscia stosu do zapisania tablicy filedesc
	_fseeki64(plik, sizeof(size_t), SEEK_SET);
	//zapisanie tablicy
	if (fwrite(fileDesc, sizeof(__int64), no_items+ 1, plik) < no_items + 1) {
		if (message(MY_MESS_PROBLEM_Z_ZAPISEM) == MY_DECISION_BREAK) {
			fclose(plik);
			file_desc_free(fileDesc);
			return;
		}
	}
	if (plik)
		fclose(plik);
	plik = NULL;
	if (fileDesc)
		free(fileDesc);
	fileDesc = NULL;
}

int  MyStackZlicz() {
	MY_STACK *p = first;
	int i = 0;
	while (p) {
		p = p->next;
		i++;
	}

	return i;
}
int My_StackOdczyt(ZapiszStudent pZaStu) {
	//Czyscimy stos
	MyStackFree();
	MY_STACK *p = first;

	//Czytamy z pliku
	size_t no_items = 0, it, rec;
	__int64 *file_desc = NULL;
	FILE *plik = NULL;

	plik = fopen("data.bin", "rb");
	if (!plik) {
		if (message(MY_MESS_PLIK) == MY_DECISION_BREAK) {
			return 0;
		}
	}
	if (fread(&no_items, sizeof(size_t), 1, plik) != 1) {
		if (message(MY_MESS_PROBLEM_Z_ODCZYTEM) == MY_DECISION_BREAK) {
			fclose(plik);
			return 0;
		}
	}
	//printf("Ilosc stosu: %d\n", no_items);
	//alokacja tablice file_desc
	file_desc = (__int64 *)malloc((no_items + 1) * sizeof(__int64));
	if (!file_desc) {
		if (message(MY_MESS_PROBLEM_Z_ALOKACJA) == MY_DECISION_BREAK) {
			fclose(plik);
			return 0;
		}
	}
	if (fread(file_desc, sizeof(file_desc[0]), no_items + 1, plik) != no_items + 1) {
		if (message(MY_MESS_PROBLEM_Z_ODCZYTEM) == MY_DECISION_BREAK) {
			fclose(plik);
			file_desc_free(file_desc);
			return 0;
		}
	}
	int year, kier;
	for (it = 0; it < no_items; ++it)
	{
		rec = no_items - it - 1;
		//utawienie na ostatni elemnt
		_fseeki64(plik, file_desc[rec], SEEK_SET);
		
		//odczyt dlugosci nazwiska
		size_t dlugosc_nazwiska = 0;
		if (fread(&dlugosc_nazwiska, sizeof(size_t), 1, plik) != 1) {
			if (message(MY_MESS_PROBLEM_Z_ODCZYTEM) == MY_DECISION_BREAK) {
				fclose(plik);
				file_desc_free(file_desc);
				return 0;
			}
		}

		//SF tego nie powinno byc w kontenerze! A jesli zmieniamy dane, ktore nie maja nazwiska, kierunku studiow i t. d.,
		//tak Pan bedzie zmienial ta funkcje stosu? 

		char nazw[256];
		//odczytujemy nazwisko
		if (fread(&nazw,sizeof(char),dlugosc_nazwiska, plik)<1) {
			if (message(MY_MESS_PROBLEM_Z_ODCZYTEM) == MY_DECISION_BREAK) {
				fclose(plik);
				file_desc_free(file_desc);
				return 0;
			}
		}
		//printf("Nazwisko: %s\n", nazw);
		if (fread(&year, sizeof(int), 1, plik)<1) {
			if (message(MY_MESS_PROBLEM_Z_ODCZYTEM) == MY_DECISION_BREAK) {
				fclose(plik);
				file_desc_free(file_desc);
				return 0;
			}
		}
		//printf("Rok Urodzenia: %d\n", year);
		if (fread(&kier, sizeof(int), 1, plik)<1) {
			if (message(MY_MESS_PROBLEM_Z_ODCZYTEM) == MY_DECISION_BREAK) {
				fclose(plik);
				file_desc_free(file_desc);
				return 0;
			}
		}
		//printf("Kierunek: %d\n", kier);
		void *pdata = (*pZaStu)(nazw, year,kier);
		MyStackDodaj(pdata);
	}
	file_desc_free(file_desc);
	fclose(plik);
	return 1;
}
void * MyStackWskaznik(int nr) {
	MY_STACK * ptr = first;
	for (int i = 0; i < nr; i++) {
		ptr = ptr->next;
	}
	return ptr;
}
void file_desc_free(__int64 *file_desc) {
	if (file_desc) {
		free(file_desc);
		file_desc = NULL;
	}
}
