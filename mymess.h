#pragma once
enum MY_MESSAGES
{
	MY_MESS_PROBLEM_Z_ALOKACJA,
	MY_MESS_BLAD_DODANIA_DO_STOSU,
	MY_MESS_PROBLEM_Z_ZAPISEM,
	MY_MESS_PROBLEM_Z_ODCZYTEM,
	MY_MESS_PLIK,
	MY_MESS_ZLY_WYBOR,
	MY_MESS_ZLA_WARTOSC,
	MY_MESS_BRAK_STOSU,
	MY_MESS_BRAK_STUDENTA,
	MY_MESS_PRZERWANO_ODCZYT,
	MY_MESS_TOTAL						     
};
enum MY_DECISION {
	MY_DECISION_BREAK,
	MY_DECISION_CONTINUE
};

enum MY_DECISION message(enum MY_MESSAGES mess);