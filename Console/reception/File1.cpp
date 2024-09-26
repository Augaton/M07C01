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
#include <sstream>
#include <fstream>

using namespace std;

string replace(char c, string replacement, string const& s)
{
    string result;
    size_t searchStartPos = 0;

    string chars = string("\\") + c;
    size_t pos = s.find_first_of(chars);
    while (pos != string::npos)
    {
        result += s.substr(searchStartPos, pos - searchStartPos);
        if (s[pos] == '\\')
        {
            result += string("\\") + c;
            searchStartPos = pos + 2;
        }
        else if (s[pos] == c)
        {
            result += replacement;
            searchStartPos = pos + 1;
        }

        pos = s.find_first_of(chars, searchStartPos);
    }

    return result;
}

 int _tmain(int argc, _TCHAR* argv[])
{

	IRServeurUDP ecoute;
	ofstream myfile;
	stringstream ss;

	char octects[300];

	ecoute.OuvrirLaSocketDEcoute(8890,"0.0.0.0");

	myfile.open ("drone_log.txt");

	do{
		ecoute.RecevoirDesOctets(octects,300);
		string msg = octects;

		size_t found=msg.find("\n\r");
		if (found!=string::npos)
		{
			msg.erase(found);
		}

		msg.replace(msg.length() - 1,1,"\" }");

		string x = ":";
		string y = "\":\"";

		size_t pos = msg.find(x);
		while (pos != string::npos)
		{
			msg.replace(pos, x.size(), y);
			pos = msg.find(x, pos + y.size());
		}

		x = ";";
		y = "\", \"";

		pos = msg.find(x)
		while (pos != string::npos)
		{
			msg.replace(pos, x.size(), y);
			pos = msg.find(x, pos + y.size());
		}


		myfile << msg;
		cout << msg;

        // hexa

		// ss << hex << msg;
		// cout << ss << endl << endl;



	}while(octects > 0);

	myfile.close();

	return 0;
}
