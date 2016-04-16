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
    void addPlace(const string& name, const Coordonnee& coord);
    void addStreet(const string& name, const list<string>& names);
    void showNeighbour(Carte carte);
    void increaseKey(map<string,int>& summitFlux, string summit, int flux);
    string extractMax(map<string,int>& summitFlux, Carte& carte, string previousSite);
    void prim(Carte& carte);

 	map<string, Coordonnee> sites;
 	map<string, int> streetInfo;

  private:
    struct Place{
        Coordonnee coord;
        map<string,string> neighbour;
    };

    map<string,Place> places;


  friend istream& operator >> (istream& is, Carte& carte);
};

#endif

