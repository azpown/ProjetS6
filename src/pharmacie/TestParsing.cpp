#include <iostream>
#include "Pharmacie.hpp"

using namespace std;

main()
{
  Pharmacie pharma("../../pharmafiles/pharma1.txt");
  pharma.affichagePharmacie();
  pharma.listeMedicament();
}
  
