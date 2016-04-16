/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Hiver 2016 / TP3
 *
 *  Décary Jean-Christophe (DECJ20119200):
 */

#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include "carte.h"
using namespace std;

void Carte::addPlace(const string& name, const Coordonnee& coord){

}
void Carte::addStreet(const string& name, const list<string>& names){
}
void Carte::showNeighbour(Carte carte){
}
void Carte::increaseKey(map<string,int>& summitFlux, string summit, int flux){
}
string Carte::extractMax(map<string,int>& summitFlux, Carte& carte, string previousSite){
return "1";
}
void Carte::prim(Carte& carte){
}




istream& operator >> (istream& is, Carte& carte){
    char separator;
    string name;
    Coordonnee coord;
    string streetName;
    int peopleFlux;
    char doublePoint;

    /*---------------------  LECTURE DES NOEUDS  --------------------*/
    is >> name;
    while(name != "---"){
    //lecture de la coordonnée
    is >>coord;
    // lecuture du point virgules
    is >> separator;
    carte.sites[name] = coord;

    is >> name;
    }

    /*-----------------------  LECTURE DES RUES  --------------------*/

    while(is >> streetName){
     list<string> siteList;
     string siteName;

     // Lecture du separateur ':'
     is >> doublePoint;
     // Lecture des sites
     is >> siteName;
     while(siteName != ";"){
        // ajout du nom du site dans la liste des sites
        siteList.push_back(siteName);
        is >> siteName;
     }
     list<string>::iterator siteIterator = siteList.end();

     //on veut aller chercher le flux de personne du segment
     string lastElement = *(--siteIterator);
     std::istringstream iss(lastElement);
     siteList.remove(lastElement);
     iss >> peopleFlux;

     carte.streetInfo[streetName] = peopleFlux;
     carte.addStreet(streetName,siteList);
    }

    carte.prim(carte);
    return is;
}

