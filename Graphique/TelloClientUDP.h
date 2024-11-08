#include <cstdlib>
#include "IRClientUDP.h"
#include "IRServeurUDP.h"
#include <string>
#include <sstream>

using namespace std;

class TelloClientUDP
{	private :
	IRClientUDP tello;
	IRServeurUDP ecoute;
	stringstream sst;
	string cmd;

	public:
	TelloClientUDP(string ip );
	string EnvoyerCommande(string commande);
	string ModeCommande();
	string Decoller();
	string Atterir();
	string Monter(int cm);
	string Descendre(int cm);
	string Gauche(int cm);
	string Droite(int cm);
	string Avant(int cm);
	string Arriere(int cm);
	string TournerHoraire(int deg);
	string TournerTrigo(int deg);

    string DeplacerXYZ(int x,int y,int z, int vitesse);
};
