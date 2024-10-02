#include <cstdlib>
#include "ServeurDonneeDrone.h"
#include "IRServeurUDP.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "IRClientTCP.h"

using namespace std;

string entetejson(string leJSON)
{
	// retirer le \n\r

	string x = "\n\r";
	string y = "";

	size_t pos = leJSON.find(x);
	while (pos != string::npos)
	{
		leJSON.replace(pos, x.size(), y);
		pos = leJSON.find(x, pos + y.size());
	}

	// moyen simple d'enlever le dernier

	leJSON.replace(leJSON.length() - 3,1,"\" }");

	// entete

	leJSON = "{ \"" + leJSON;

	// remplacement ":"

	x = ":";
	y = "\":\"";

	pos = leJSON.find(x);
	while (pos != string::npos)
	{
		leJSON.replace(pos, x.size(), y);
		pos = leJSON.find(x, pos + y.size());
	}

	// remplacement ";"

	x = ";";
	y = "\", \"";

	pos = leJSON.find(x);
	while (pos != string::npos)
	{
		leJSON.replace(pos, x.size(), y);
		pos = leJSON.find(x, pos + y.size());
	}

	return leJSON;
}

ServeurDonneeDrone::ServeurDonneeDrone(string pilote, string numeroDrone)
{
	OuvrirFichierLog("ServeurLog");
	bool Link = serveurUDP.OuvrirLaSocketDEcoute(8890);
	if(Link) std::cout << "Requete Link" << Link;
    DebuterJSON(pilote, numeroDrone);
	recus = 0;
    
}

void ServeurDonneeDrone::OuvrirFichierLog(string nomFichier)
{
	nomFichier = nomFichier + ".txt";
	const char *filename = nomFichier.c_str();
	fichierLog.open(filename);
}

void ServeurDonneeDrone::AjoutFichierLog(string texte)
{
	fichierLog << texte;
}

void ServeurDonneeDrone::FermerFichierLog()
{
	fichierLog.close();
}

int ServeurDonneeDrone::RecevoirDonneesDrone()
{

	int recusmsg = serveurUDP.RecevoirUnMessage(recusmsgstring,1000000);
	if (recusmsg == 0) {
		cout << "timeout" << endl;
		FermerFichierLog();
		return 0;
	}

	AjoutFichierLog(recusmsgstring);
	
	if (recus == 0){
		recusmsgstring = entetejson(recusmsgstring);
		recus = recus + 1;
	} 
	else
	{
		recusmsgstring = "," + entetejson(recusmsgstring);
	}

	AjouterDonneesJSON(recusmsgstring);

	return recusmsgstring.length();
}

void ServeurDonneeDrone::CreerJSON(string pilote, string numeroDrone)
{

}

void ServeurDonneeDrone::EnvoyerDonneesBDD(string IPREST,string urlREST)
{
	CloreJSON();
	clienttcp.SeConnecterAUnServeur(IPREST,80);

	stringstream slongeur;
	slongeur<<leJSON.length();

	string requete = "POST "+urlREST+" HTTP/1.1\r\nHost: "+IPREST+"\r\nConnexion: keep-alive\r\nContent-type: text/plain\r\nContent-Length: "+slongeur.str()+"\r\n\r\n"+leJSON;

	clienttcp.Envoyer(requete);
}

void ServeurDonneeDrone::DebuterJSON(string pilote, string numeroDrone)
{
	string donneesvolentete =  "{ \"donneesVol\": {";

	string nomentete = "\"nom\": \" "+ pilote +" \",";
	string numeroentete = "\"numero\": \" "+ numeroDrone +" \",";

	stringstream stimestamp;
	int timestamp = (int)time(NULL);
	stimestamp<< "\"time\": \"";
	stimestamp<<timestamp<<"\",";

	string etatsentete =  "\"etats\": [";

	leJSON = donneesvolentete + nomentete + numeroentete + stimestamp.str() + etatsentete;

}

void ServeurDonneeDrone::AjouterDonneesJSON(string message)
{
	leJSON = leJSON + message;
}

void ServeurDonneeDrone::CloreJSON()
{
	leJSON = leJSON + "]}}";

	fichierLog.open("drone.json");
	fichierLog << leJSON;
	fichierLog.close();
}



