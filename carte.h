/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Automne 2015/ TP3
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
 #include <set>
#include <string>
#include <vector>

 using namespace std;

 class Carte{
 public:
 	void ajouterLieu(const string& nom, const Coordonnee& c);
 	void ajouterRoute(const string& nom, const list<string>& noms);
 	void afficherVoisins(Carte cart);
 	void incraseKey(map<string,int>& sommetFloux, string sommet, int floux);
 	string extractMax(map<string,int>& sommetFloux,Carte& carte,string sitePrece);
 	void prim(Carte& carte);
 	map<string, Coordonnee> sites;
 	map<string, int> infoRue; 

 private:
 	struct Lieu{
        Coordonnee coor;     
        map<string,string> voisins; // <site rue>

    };
    
    map<string, Lieu> lieux;


    
    friend istream& operator >> (istream& is, Carte& carte);
};

#endif

