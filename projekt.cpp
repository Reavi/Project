// projekt.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
// Mielec Krystian
// GL 05

#include "stdafx.h"
#include "mydata.h"
#include "myinterface.h"
#include "mystack.h"


int main()
{
	MyStackInit(MyDataFree);
	MyInterfaceMenu();
	MyStackFree();
    return 0;
}

