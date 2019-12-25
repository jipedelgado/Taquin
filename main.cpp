/*version du 2014/11/28
 * auteur = jipedelgado@gmail.com
 *
 * OBJECTIF =
 * A partir d'une configuration donnée par aString, déterminer la suite
 * de longueur minimale de tableaux ( obtenus par le déplacement de la valeur zéro
 * dans cette chaine, respectant les règles du jeu du Taquin) ,
 * qui mène à la suite naturelle "0 1 2 3 ..."
 *
 * Algorithme inspiré largement de <retrouver l'auteur>
 *
 *  AVERTISSEMENT
 * Une exception c00000fd "stack overflow" se produit dans certaines configurations
 * en particulier quand Stack.Size est supérieur à 21569 pour un carré de 5x5
 *
 * TODO = 2014/11/28 =
 *  catcher cette exception, ou résoudre le problème
 *    pistes = la cause possible est l'utilisation de la récursivité sur compute()
 *  Implémenter input
 *  améliorer l'affichage des résultats
 *
 */

#include <QApplication>
#include "MainWindow.h"
#include "Tableau.h"
#include "Taquin.h"

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>      // pour compteur de vitesse

using namespace std;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  string aString = "1 2 3 4 5 6 7 8 9 10 11 12 13 0 14 15 16 17 18 19 20 21 22 23 24";

  Taquin myTaquin(aString);

  // vérification de la parité de aString, qui doit être la même que celle de la chaine de destination,
  // elle-même de parité paire
  if(myTaquin.parite(myTaquin.EtatFinal.EtatCourant)%2 != 0){
      cout<<"resolution impossible, parite impaire"<<endl;
      exit(EXIT_FAILURE);
  }
  else{
      DWORD debut = GetTickCount();
      try{
        myTaquin.compute(myTaquin.EtatFinal,20317);
      }
      catch(exception& e){
        cout << "An exception occurred. Exception Nr. " << e.what() << '\n';
      }
      DWORD end = GetTickCount();
      cout<<"# temps d'execution = "<<end - debut<<endl;
    }

      cout<<"# suite gagnante   = "<<myTaquin.EtatFinal.Genealogie<<endl;
      cout<<"# nb etats traites = "<<myTaquin.nbEtatsTraites<<endl;
      cout<<"# nombre de coups  = "<<myTaquin.EtatFinal.Genealogie.size()<<endl<<endl;


      vector<Tableau> suite = myTaquin.SuiteDeCoupsGagnants(myTaquin.EtatFinal.Genealogie);
      cout<< "# la suite des etats est \n"<<endl;
      for(size_t i=0; i<suite.size();i++)
          cout<< "**** "<<suite.at(i).toString()<<endl;

  return a.exec();
}
