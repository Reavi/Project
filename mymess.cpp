#include "stdafx.h"
#include "mymess.h"
static char *my_message_str_tab[] = {
	"EProblem z alokacja pamieci\n",
	"EProblem z dodaniem do stosu!\n",
	"EProblem z zapisem do pliku!\n",
	"EProblem odczytania z pliku!\n",
	"EProblem z otwarciem pliku!\n",
	"WBrak takiego wyboru!\n",
	"WProsze wpisac prawidlowa wartosc!\n",
	"MStos nie istnieje!\n",
	"MBrak studenta!\n",
	"MPrzerwano funkcje odczytujaca z pliku!\n"

};
enum MY_DECISION message(enum MY_MESSAGES mess) {
	MY_DECISION retval = MY_DECISION_CONTINUE;

	puts(my_message_str_tab[mess] + 1);

	if (my_message_str_tab[mess][0] == 'E') {
		retval = MY_DECISION_BREAK;
	}
	return retval;
}