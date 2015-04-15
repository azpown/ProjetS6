#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>
#include <unordered_map>
#include "Pharmacie.hpp"

#define DEBUG 1

using namespace std;

#define SAUT_LIGNE cout << "\n"
#define VALUE_POSSIBLE 35
#define POSSIBLY_GL(length) if(length< VALUE_POSSIBLE) return

inline 
int seekAndReplaceOnce(string & line,string seek,string replace) 
{
  size_t pos=line.find(seek);
  if(pos != string::npos)
  {
    #ifdef DEBUG
    cout << "POS,SEEK.LENGHT,REPLACE : " << pos << " " << seek.length() << " " << replace << "\n";
    #endif
    line.replace(pos,seek.length(), replace);
  } 
} 

Pharmacie::Pharmacie(string s)
{
  /* Constructeur de ifstream prend des char * et non des string -> donc appel méthode
     c_str() de la classe string. */
  ifstream input(s.c_str());
  if(input.good()) //vérifie que le fichier est valide
    parsePharma(input);
  else
    throw runtime_error("Incorrect file file");
}

void Pharmacie::parsePharma(ifstream& in)
{
  string s;
  while(in.good())
  { // tant que le fichier n'est pas vide
    s = '\0';
    getline(in,s,'\n'); /* \n defini comme caractere de fin de ligne */
    parseMed(s);
  }
}

/* Pas besoin d'allocation dynamique sur ces données nécessaire */
void Pharmacie::parseMed(string s)
{
  /* Etape 0 : Formatage de la chaine */
  POSSIBLY_GL(s.length());
  string & myString = s;
  seekAndReplaceOnce(myString,", et",",");
  seekAndReplaceOnce(myString,"  et",",");
  seekAndReplaceOnce(myString," et",",");
  #ifdef DEBUG
  cout << "Line after process : \n" << s << "\n";
  #endif
  /* Etape 1 : Parsing du nom */
  size_t z = s.find(':');
  size_t t = 0;
  string name= s.substr(0, z-1); 
  // nom du médicament (de la position 0 dans le string à z-1, vu qu'il y a un espace avant ':')
  /* Etape 2 : Parsing des effets secondaires */
  vector<string> effects;
  /* On se positionne sur la premiere lettre du premier effet secondaire */  
  t = s.rfind(':')+2;
  while(t < s.length())
  { 
    // boucle jusqu'à la fin de la ligne
    z = s.find(',', t);
    if( z  == std::string::npos)
    {
      /* traitement du dernier effet secondaire */
      z = s.find(".",t);
      effects.push_back(s.substr(t, z-t));	
      break;
    }
    else
    { 
      // il y a plusieurs effets secondaires à traiter encore
      effects.push_back(s.substr(t, z-t));
      t = z+2;	
      // on fait avancer i de la taille de la chaine + l'espace et la virgule
    }
  }
  meds.insert(pair<string, vector<string> >(name, effects)); //insertion de la paire représentant le médicament dans la map
}



/* Affichage des données */
/* TODO : Factorisation de code */

void Pharmacie::affichagePharmacie()
{
  cout << "\t-*- PHARMACIE -*-\t\n\n";
  for (unordered_map< string,vector<string> >::iterator it1=meds.begin();\
       it1!=meds.end();++it1)
  {
    cout << "NOM DU MEDICAMENT : \n" << it1->first << "\n\n";
    cout << "EFFETS SECONDAIRE : " << "\n";
    for(vector<string>::iterator it2 = it1->second.begin();\
	it2!=it1->second.end();++it2)
      cout << (*it2) << "\n";
    SAUT_LIGNE;
  }
  SAUT_LIGNE;
}

/* Factorisation réalisable via macro, mais peu lisible */
void Pharmacie::listeMedicament()
{
  cout << "LISTE DE MEDICAMENT : \n";
  for (unordered_map< string,vector<string> >::iterator it =meds.begin();it !=meds.end(); ++it)
    cout << it->first << " | "; 
  SAUT_LIGNE;
}
  
void Pharmacie::buildReverseMeds()
{
  cout << "CREATION REVERSE MAP POUR HISTO : \n";
  map<string, vector<string*> >::iterator finded; 
  for (unordered_map< string,vector<string> >::iterator it1 =meds.begin();it1 !=meds.end(); ++it1)
  {
    for(vector<string>::iterator it2 = it1->second.begin();it2!=it1->second.end();++it2)
    {
      /*On regarde si l'effet secondaire est dans la map, sinon on l'ajoute*/
      finded = reverseMeds.find(*it2);
      if(finded == reverseMeds.end())
	addReverseMap((*it2),it1->first);
      /* Sinon il suffit d'add un pointeur sur le médicament au bon vecteur */
      else
	it1->second.pushback(it1->(&first));
    }
  }
}

void Pharmacie::addReverseMap(string effetSec,string medoc)
{
  vector<string> medocs;
  medocs.pushback(medoc);
  reverseMeds.insert(pair<string, vector<string*> >(effetSec,medocs)); //insertion de la paire représentant le médicament dans la map
}
      
  
