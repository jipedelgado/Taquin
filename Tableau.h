/* 
 * File:   Tableau.h
 * Author: jipedelgado@gmail.com
 *
 * Created on 20 décembre 2012, 23:43
 * 2014/11/27 = surchargé opérateur() de comparaison pour utilisation de
 * priority_queue dans Taquin.h
 */

#ifndef TABLEAU_H
#define	TABLEAU_H
#include <iostream>
#include <string>
#include <vector>
//#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Tableau {
private:
    string HashKey;
    void setCoteDuTableau();
    void setCoteDuTableau(int); 
public:
    string Genealogie;
    string getStringFromVectorInt(vector<int>);
    int Value;    
    int nombreDeCases; 
    vector<int> EtatCourant;
    static const char separateur = ' '; 
    int coteDuTableau;
    
    Tableau();
    explicit Tableau(string);
    explicit Tableau(vector<int>);
    virtual ~Tableau();
    
    bool operator<( Tableau&);
    vector<Tableau> Fils();
    Tableau Joue(string);
    string toString(void); 
    void setHashKey(void);
    string getHashKey(void);
    void setEtatFinal(string);
    int getDistanceTo(const Tableau&);
    void computeAbsoluteValue(void);  //depuis le tableau canonique
    int getValue(void);
    void setGenealogie(string);
    string getGenealogie(void);
    int nbInversions(vector<int>);
    int positionZero(vector<int>);
    Tableau play(char);

    bool operator()(const Tableau& t1, Tableau& t2){
      return (t1.Value > t2.Value);
    }

};



#endif	/* TABLEAU_H */
