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
 list<string>::const_iterator streetIterator = names.begin();
 if(streetIterator == names.end()) return;
 list<string>::const_iterator cloneStreetIterator = streetIterator;
 ++cloneStreetIterator;
 while(cloneStreetIterator != names.end()){
    places[*streetIterator].neighbours[*cloneStreetIterator] == name ;
    places[*cloneStreetIterator].neighbours[*streetIterator] == name ;
    streetIterator = cloneStreetIterator;

    ++cloneStreetIterator;
 }
}
void Carte::showNeighbour(Carte carte){
    for(map<string,Place>::iterator placeIterator = carte.places.begin(); placeIterator != carte.places.end(); placeIterator ++){
        cout << "nom site : " <<  placeIterator->first<< " voisins :" << endl;
        for(map<string,string>::iterator neighbourIterator = placeIterator->second.neighbours.begin(); neighbourIterator != placeIterator ->second.neighbours.end(); neighbourIterator++){
            cout << " " << neighbourIterator->first  ;
            cout << " nom de la rue " << neighbourIterator->second  ;
            cout << " floux " << carte.streetInfo[neighbourIterator->second] << endl ;
        }
    }
}
void Carte::increaseKey(map<string,int>& summitFlux, string summit, int flux){
  summitFlux[summit] = flux;
}
string Carte::extractMax(map<string,int>& summitFlux, string previousSite){
  int min = numeric_limits<int>::min();
  int currentRange = 0;
  int selectedRange = 0;
  string site;

  for(map<string,int>::iterator fluxIterator = summitFlux.begin(); fluxIterator != summitFlux.end(); fluxIterator++){
        if(fluxIterator-> second == min){
            currentRange = sites[previousSite].distance(sites[fluxIterator->first]);
            selectedRange = sites[previousSite].distance(sites[site]);

            if(currentRange > selectedRange){
                continue;
            }
        }
        if(fluxIterator->second >= min){
            site = fluxIterator->first;
            min = fluxIterator->second;
        }
  }
  summitFlux.erase(site);
  return site;
}
void Carte::print(){
 list<string> results;
 map<string,int> summitFlux;
 map<string, map<string,string> > nextSummit;
 string previousSite;
 int sum = 0;
 int min = numeric_limits<int>::min();


 for(map<string,Coordonnee>::iterator siteIterator = sites.begin(); siteIterator != sites.end(); siteIterator++){
    summitFlux[siteIterator->first]= min;
 }

 increaseKey(summitFlux,summitFlux.begin()->first,0);

 while(!summitFlux.empty()){
    string site = extractMax(summitFlux,previousSite);
    previousSite = site;
    results.push_back(site);
    for(map<string,string>::iterator neighbourIterator = places[site].neighbours.begin(); neighbourIterator != places[site].neighbours.end(); neighbourIterator++){
        if((summitFlux.count(neighbourIterator->first) != 0) && (streetInfo[neighbourIterator ->second]> summitFlux[neighbourIterator-> first])){
            map<string,string> temporary;
            temporary[site] = neighbourIterator->first;
            nextSummit[neighbourIterator->first] = temporary;
            increaseKey(summitFlux, neighbourIterator->first, streetInfo[neighbourIterator->second]);
        }
    }
 }
 list<string>::iterator resultIterator = results.begin();
 ++resultIterator;

 for(; resultIterator != results.end(); ++resultIterator){
    cout <<  nextSummit[*resultIterator].begin()->first << " "<< nextSummit[*resultIterator].begin()->second << endl;
    cout <<  places[nextSummit[*resultIterator].begin()->first].neighbours[nextSummit[*resultIterator].begin()->second] << endl;
    cout <<  streetInfo[places[nextSummit[*resultIterator].begin()->first].neighbours[nextSummit[*resultIterator].begin()->second]] << endl;
    sum += streetInfo[places[nextSummit[*resultIterator].begin()->first].neighbours[nextSummit[*resultIterator].begin()->second]];
    }
    cout <<  "---" << endl;
    cout <<  sum << endl;


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
    return is;
}

