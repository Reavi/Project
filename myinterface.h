#pragma once

enum MY_INTERFACE{
	INTERFACE_KONIEC,
	INTERFACE_DODAJ,
	INTERFACE_USUN,
	INTERFACE_ZNAJDZ,
	INTERFACE_POKAZ,
	INTERFACE_ZAPISZ_DO_PLIKU,
	INTERFACE_ODCZYT_Z_PLIKU,
	INTERFACE_TOTAL
};
void MyInterfaceMenu();
static void MyInterfaceDodaj();
static void MyInterfaceUsun();
static void MyInterfaceZnajdz();
static void menu();
static void MyInterfaceZapisz();
static void MyInterfaceOdczyt();
static void MyInterfacePokazKierunki();
static void MyInterfaceUsunPierwszy();
static void MyInterfaceUsunWszystkich();
static void MyInterfacePokaz();
static void MyInterfacePokazWszystkich();
static void MyInterfacePokazJeden();
static void MyInterfaceZnajdzNazwisko();
static void MyInterfaceZnajdzRok();
static void MyInterfaceZnajdzKierunek();