#include "TelloClientUDP.h"
#include "IRClientUDP.h"
#include "IRServeurUDP.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

TelloClientUDP::TelloClientUDP(string ip)
{
	tello.OuvrirLaSocketDeCommunication(ip,8889);
	ecoute.OuvrirLaSocketDEcoute(8890,ip);

}

string TelloClientUDP::EnvoyerCommande(string commande)
{
	tello.EnvoyerUnMessage(commande);
	string msg;

	tello.RecevoirUnMessage(msg);

	return msg;
}

string TelloClientUDP::ModeCommande()
{
	cmd="command";
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Decoller()
{
	cmd="takeoff";
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Atterir()
{
	cmd="land";
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Monter(int cm)
{
	sst.str("");
	sst<<cm;
	cmd="up " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Descendre(int cm)
{
	sst.str("");
	sst<<cm;
	cmd="down " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Gauche(int cm)
{
	sst.str("");
	sst<<cm;
	cmd="left " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Droite(int cm)
{
	sst.str("");
	sst<<cm;
	cmd="right " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Avant(int cm)
{
	sst.str("");
	sst<<cm;
	cmd="forward " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::Arriere(int cm)
{
	sst.str("");
	sst<<cm;
	cmd="back " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::TournerHoraire(int deg)
{
	sst.str("");
	sst<<deg;
	cmd="cw " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::TournerTrigo(int deg)
{
	sst.str("");
	sst<<deg;
	cmd="ccw " + sst.str();
	return EnvoyerCommande(cmd);
}

string TelloClientUDP::DeplacerXYZ(int x,int y,int z, int vitesse)
{   stringstream sst; sst<<x<<" "<<y<<" "<<z<<" "<<vitesse;
	cmd="go "+sst.str();
	return EnvoyerCommande(cmd);
}


