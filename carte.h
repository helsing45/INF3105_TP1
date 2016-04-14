/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2016/ TP3
 *
 *  Vos noms + codes permanents :
 */
 
#if !defined(_CARTE__H_)
#define _CARTE__H_
#include "coordonnee.h"
#include <cassert>
#include <istream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Carte{
  public:


  private:

    
  friend istream& operator >> (istream& is, Carte& carte);
};

#endif

