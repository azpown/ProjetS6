#ifndef __PHARMACIE_HPP
#define __PHARMACIE_HPP

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Pharmacie{
private:
  unordered_map<string, vector<string> > meds; //Medicament
  map<string, vector<string*> > reverseMeds; // Contruction pour un histo plus rapide pour de multiple utilisation.
  unsigned int nMedicament;
  unsigned int nEffetSecondaire;
public:
  Pharmacie(string);
  void addReverseMap(string effetSec,string medoc);
  void buildReverseMeds();
  void parsePharma(ifstream&); // parse le fichier d'entrée
  void parseMed(string); // parse un médicament
  void affichagePharmacie();
  void listeMedicament();
};

#endif
