#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include "IRServeurUDP.h"
#include <iostream>
#include <string>

using namespace std;

 int _tmain(int argc, _TCHAR* argv[])
{

	IRServeurUDP ecoute;

	char octects[100];

	ecoute.OuvrirLaSocketDEcoute(8890,"0.0.0.0");

	do{
	   ecoute.RecevoirDesOctets(octects,100);

	   cout << octects << endl;



	}while(octects > 0);
	return 0;
}