#include <cstdlib>
#include "IRServeurUDP.h"
#include <string>
#include <sstream>

using namespace std;

class ServeurDonneeDrone
{	private :
	IRServeurUDP ecoute;
	stringstream sst;
	string cmd;

	public:
	ServeurDonneeDrone(string pilote, string numeroDrone );
	void AjouterDonneesJSON(string message);
	void FermerFichierLog();
	int RecevoirDonneesDrone();
	void AjoutFichierLog(string texte);
	void AjoutDonn(string texte);
	string DebuterJSON(int cm);
	string CloreJSON(int cm);
	string Gauche(int cm);
	string Droite(int cm);
	string Avant(int cm);
	string Arriere(int cm);
	string TournerHoraire(int deg);
	string TournerTrigo(int deg);
};
