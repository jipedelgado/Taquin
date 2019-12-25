/*
 * File:   Taquin.cpp
 * Author: utilisateur
 *
 * Created on 20 décembre 2012, 22:51
 *
 * 2014/11/27 = remplacement de vector<Tableau> par priority_queue<>
 * => gain de temps  = 50%, de 31 à 15 ticks pour tableau 4x4
 *
 * 2014/11/28 =
 * remplacement de map<string, int> EnsembleExplore
 * par unordered_set <string> EnsembleExplore;
 *
 */

#ifndef _TAQUIN_H
#define	_TAQUIN_H

//#include "ui_Taquin.h"
#include "Tableau.h"

// tout ça pour debugger avec cout<<
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>          // facilite les conversions de type size_t et int
#include <vector>
#include <unordered_set>
#include <queue>
#include <sstream>

class Taquin {
  //  Q_OBJECT

private:
   // Ui_Taquin widget;
    int Size;
    unordered_set <string> EnsembleExplore;
    priority_queue< Tableau, vector<Tableau>, Tableau >  Stack;

public:
    Tableau EtatInitial;
    Tableau EtatFinal;
    Taquin(void);
    Taquin(int);
    Taquin(int,string);
    Taquin(string);
    virtual ~Taquin();
    long int nbEtatsTraites;
    
    void setTaquin(string);
    void compute( Tableau&, int);
    int parite(vector<int>);
    vector<int> wrap(vector<int>, int);
    string getStringFromVectorInt(const vector<int>, size_t, size_t );
    int positionZero(vector<int>);
    vector<Tableau> SuiteDeCoupsGagnants(string);


};



#endif	/* _TAQUIN_H */
