#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <iostream>
#include <string>
#include "TelloClientUDP.h"

using namespace std;

 int _tmain(int argc, _TCHAR* argv[])
{
	char choix[100];
	string cmd;
	int x, y;
	string ip;

	cout<<"Entrer l'ip du drone :"<<endl;
	cin >> ip;
	TelloClientUDP drone(ip);

	do{

		cout<<"C - Ciel"<<endl;
		cout<<"S - Sol"<<endl;
		cout<<"H - Haut                   [H=25cm  HH=50cm ...]" << endl;
		cout<<"B - Bas                    [B=25cm  BB=50cm ...]" << endl;
		cout<<"G - Gauche                 [G=25cm  GG=50cm ...]" << endl;
		cout<<"D - Droite                 [D=25cm  DD=50cm ...]" << endl;
		cout<<"A - Avancer                [A=25cm  AA=50cm ...]" << endl;
		cout<<"R - Reculer                [R=25cm  RR=50cm ...]" << endl;
		cout<<"P - Pivoter sens horaire   [P=30deg PP=60deg...]" << endl;
		cout<<"T - Tourner sens trigo     [T=30deg TT=60deg...]" << endl;
		cout<<"M - Mode Commande"<<endl;
		cout<<"Q - Quitter"<<endl;

		cin >> choix;

		x = (strlen(choix) * 25);
		if (x > 180) {
			x = 1;
		}
		y = (strlen(choix) * 30);
		if (y > 180) {
			y = 1;
		}

		switch (choix[0])
		{
		case 'c': case 'C': drone.Decoller(); 				break;
		case 's': case 'S': drone.Atterir(); 				break;
		case 'h': case 'H': drone.Monter(x); 				break;
		case 'b': case 'B': drone.Descendre(x); 			break;
		case 'g': case 'G': drone.Gauche(x); 				break;
		case 'd': case 'D': drone.Droite(x); 				break;
		case 'a': case 'A': drone.Avant(x); 				break;
		case 'r': case 'R': drone.Arriere(x); 				break;
		case 'p': case 'P': drone.TournerHoraire(y); 		break;
		case 't': case 'T': drone.TournerTrigo(y); 			break;
		case 'm': case 'M': drone.ModeCommande(); 			break;
		case 'q': case 'Q': cout << "Aurevoir"; 	  return true;

		default: cout<<"Erreur commande"; break;
		}

	}while(true);

	return 0;
}
