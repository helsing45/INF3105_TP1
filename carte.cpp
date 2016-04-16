/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Automne 2015 / TP3
 *
 *  Vos noms + codes permanents :
 */
#include <iostream>
#include <cstdio>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include "carte.h"
#include <string>

 using namespace std;

void Carte::ajouterRoute(const string& nomroute, const list<string>& route){
    list<string>::const_iterator iter1=route.begin();
    if(iter1==route.end()) return;
    list<string>::const_iterator iter2=iter1;
    ++iter2;
    while(iter2!=route.end()){
        lieux[*iter1].voisins[*iter2] = nomroute;
        lieux[*iter2].voisins[*iter1] = nomroute;
        iter1 = iter2;
        ++iter2;
    }
}

void Carte::afficherVoisins(Carte carte){


    for (std::map<string, Lieu>::iterator it=carte.lieux.begin(); it != carte.lieux.end(); it++){

        cout << "nom site : " <<  it->first<< " voisins :" << endl;

        for(std::map<string,string>::iterator it2= it->second.voisins.begin(); it2 != it->second.voisins.end(); it2++){

            cout << " " << it2->first  ;
            cout << " nom de la rue " << it2->second  ;
            cout << " floux " << carte.infoRue[it2->second] << endl ;
        }
        cout << "." << endl;

    }
}

void Carte::incraseKey(map<string,int>& sommetFloux, string sommet, int floux){

 sommetFloux[sommet] = floux;

}

string Carte::extractMax(map<string,int>& sommetFloux, Carte& carte, string sitePrece){

    int min = numeric_limits<int>::min();
    int distanceCourrant = 0;
    int distanceSelectione = 0;
    string site;
    for (std::map<string, int>::iterator it=sommetFloux.begin(); it != sommetFloux.end(); it++)
    {
        if (it->second == min){
            distanceCourrant = sites[sitePrece].distance(sites[it->first]);
            distanceSelectione = sites[sitePrece].distance(sites[site]);
            if (distanceCourrant > distanceSelectione){
                continue;
            }

        }
        if(it->second >= min){
            site = it->first;
            min = it->second;
        }
    }
    sommetFloux.erase (site);
    return site;
}

void Carte::prim(Carte& carte){

    list<string> resultat;
    map<string,int> sommetFloux;
    map< string,map<string,string> > sommetSuivant;
    string sitePrece;
    int somme = 0;
    int min = numeric_limits<int>::min();
    for (std::map<string, Coordonnee>::iterator it=carte.sites.begin(); it != carte.sites.end(); it++)
    {
        sommetFloux[it->first] = min;
    }

    carte.incraseKey(sommetFloux,sommetFloux.begin()->first, 0);

    while (!sommetFloux.empty()){

        string site = extractMax(sommetFloux,carte,sitePrece);
        sitePrece = site;
        resultat.push_back(site);

        for (std::map<string, string>::iterator it=carte.lieux[site].voisins.begin(); it != carte.lieux[site].voisins.end(); it++)
        {

            if ( (sommetFloux.count(it->first) != 0) && (carte.infoRue[it->second] > sommetFloux[it->first]) )
            {

                map <string,string>  tmp;
                tmp[site] = it->first ;
                sommetSuivant[it->first] =  tmp;
                incraseKey(sommetFloux,it->first, carte.infoRue[it->second]);

            }
        }
    }
    list<string>::iterator it =resultat.begin();
    ++it;
    for (; it!=resultat.end(); ++it)
    {
        cout <<  sommetSuivant[*it].begin()->first << " "<< sommetSuivant[*it].begin()->second << endl;
        cout <<  carte.lieux[sommetSuivant[*it].begin()->first].voisins[sommetSuivant[*it].begin()->second] << endl;
        cout <<  carte.infoRue[carte.lieux[sommetSuivant[*it].begin()->first].voisins[sommetSuivant[*it].begin()->second]] << endl;
        somme += carte.infoRue[carte.lieux[sommetSuivant[*it].begin()->first].voisins[sommetSuivant[*it].begin()->second]];
    }
    cout <<  "---" << endl;
    cout <<  somme << endl;


}



istream& operator >> (istream& is, Carte& carte)
{

    string nomSite;
    Coordonnee coor;
    string nomRue;
    int floux;
    char doublePoint;


    is >> nomSite;
    while(nomSite != "---"){
      //cout << nomSite << endl;
      is >> coor ;
     // cout << coor << endl;
      carte.sites[nomSite] = coor;
      is >> nomSite;
  }


  while(is >> nomRue){
    list<string> listeSites;
    string nomSite;

    //cout << nomRue << endl;
    is >> doublePoint;
    assert(doublePoint == ':');
    is >> nomSite;
    while(nomSite != ";" ){
     //cout << nomSite << endl;
     listeSites.push_back(nomSite);
     is >> nomSite;
 }

 list<string>::iterator iter = listeSites.end();

 string dernierElement = *(--iter);
 std::istringstream iss(dernierElement);
 listeSites.remove(dernierElement);
 iss >> floux;

 carte.infoRue[nomRue] = floux;
 carte.ajouterRoute(nomRue, listeSites);

}

//carte.afficherVoisins(carte);
carte.prim(carte);

return is;
}

