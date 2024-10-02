#include <cstdlib>
#include "IRServeurUDP.h"
#include "IRClientTCP.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class ServeurDonneeDrone
{	private :
	ofstream fichierLog;
	IRServeurUDP serveurUDP;
	IRClientTCP clienttcp;
	string leJSON;
	char octects[300];
	string recusmsgstring;
	int recus;

	public:
	ServeurDonneeDrone(string pilote, string numeroDrone );
	void OuvrirFichierLog(string nomFichier);
	void AjoutFichierLog(string texte);
	void FermerFichierLog();
	int RecevoirDonneesDrone();
	void CreerJSON(string pilote, string numeroDrone);
	void EnvoyerDonneesBDD(string IPREST,string urlREST);
	void DebuterJSON(string pilote, string numeroDrone);
	void AjouterDonneesJSON(string message);
	void CloreJSON();
};
