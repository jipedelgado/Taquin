
#include "Tableau.h"

using namespace std;

Tableau::Tableau(){}
Tableau::Tableau(string aString) {
   nombreDeCases = 0;
   char charRead ;
   string tempoString;
   int tempoStringToInt;
   do{
	charRead = aString.at(0); 
	aString.erase(0, 1);
	if ( charRead == separateur) {
	    stringstream(tempoString) >> tempoStringToInt;
	    EtatCourant.push_back(tempoStringToInt);
	    tempoString.clear();
	    nombreDeCases++;
	} 
	else tempoString += charRead;
    }
    while (!aString.empty());
    stringstream(tempoString) >> tempoStringToInt;
    EtatCourant.push_back(tempoStringToInt);
    nombreDeCases++;
    setCoteDuTableau();
    computeAbsoluteValue();
    Genealogie.append("@");
    setHashKey();
}
Tableau::Tableau(vector<int> unEtat){
    EtatCourant = unEtat;
    nombreDeCases = unEtat.size();
    setCoteDuTableau();  
    computeAbsoluteValue();
    Genealogie.append("@");
    setHashKey();
}
Tableau::~Tableau() {}
bool Tableau::operator <( Tableau& t){
    return Value < t.Value;
}
vector<Tableau> Tableau::Fils(){
    vector<Tableau> aVector;
    size_t positionDeZero = 0;
    int tempoSwap = 0;
    int decalage = 0;

    while(EtatCourant.at(positionDeZero) != 0 
	    &&  positionDeZero< EtatCourant.size())
	positionDeZero++;
    
    if(positionDeZero >= coteDuTableau && Genealogie.at(Genealogie.size()-1)!='B') {
	decalage = -coteDuTableau;
	vector<int> NouvelEtat = EtatCourant;
	tempoSwap = NouvelEtat[positionDeZero];
	NouvelEtat[positionDeZero] = NouvelEtat[positionDeZero+decalage];
	NouvelEtat[positionDeZero+decalage] = tempoSwap;
	Tableau nouveauTableau = Tableau(NouvelEtat);
	nouveauTableau.Genealogie = Genealogie;
	nouveauTableau.Genealogie.append("H");
	aVector.push_back(nouveauTableau);	
    }
    if(positionDeZero % coteDuTableau != 0 && Genealogie.at(Genealogie.size()-1)!='D') {
	decalage = -1;
	vector<int> NouvelEtat = EtatCourant;
	tempoSwap = NouvelEtat[positionDeZero];
	NouvelEtat[positionDeZero] = NouvelEtat[positionDeZero+decalage];
	NouvelEtat[positionDeZero+decalage] = tempoSwap;
	Tableau nouveauTableau = Tableau(NouvelEtat);
	nouveauTableau.Genealogie = Genealogie;
	nouveauTableau.Genealogie.append("G");	
	aVector.push_back(nouveauTableau);		
    }
    if(positionDeZero % coteDuTableau != coteDuTableau-1  && Genealogie.at(Genealogie.size()-1)!='G'){
	decalage = 1;
	vector<int> NouvelEtat = EtatCourant;
	tempoSwap = NouvelEtat[positionDeZero];
	NouvelEtat[positionDeZero] = NouvelEtat[positionDeZero+decalage];
	NouvelEtat[positionDeZero+decalage] = tempoSwap;
	Tableau nouveauTableau = Tableau(NouvelEtat);
	nouveauTableau.Genealogie = Genealogie;
	nouveauTableau.Genealogie.append("D");
	aVector.push_back(nouveauTableau);		
    }
    if(positionDeZero < coteDuTableau*coteDuTableau-coteDuTableau  && Genealogie.at(Genealogie.size()-1)!='H'){
	decalage = coteDuTableau;
	vector<int> NouvelEtat = EtatCourant;
	tempoSwap = NouvelEtat[positionDeZero];
	NouvelEtat[positionDeZero] = NouvelEtat[positionDeZero+decalage];
	NouvelEtat[positionDeZero+decalage] = tempoSwap;
	Tableau nouveauTableau = Tableau(NouvelEtat);
	nouveauTableau.Genealogie = Genealogie;
	nouveauTableau.Genealogie.append("B");
	aVector.push_back(nouveauTableau);		
    }
    return aVector;
}
void Tableau::setHashKey(void){
   /* une solution rapide pourrait-etre: 
    * HashKey = getStringFromVectorInt(EtatCourant); 
    * une solution standard pourrait-etre: HashKey = hash<string> mais
    *   hash n'est pas implémenté dans cette distribution
    * mais voici une une solution spécifique
    */
    string separateurLocal = "-";
    char buffer [33];
    for(int i = 0; i<nombreDeCases-1; i++){
	HashKey += itoa(EtatCourant[i],buffer,10);
	HashKey += separateurLocal;    
    }
    HashKey += itoa(EtatCourant[nombreDeCases-1],buffer,10);
}
void Tableau::setCoteDuTableau(int valeur){
    coteDuTableau = valeur;
}
void Tableau::setCoteDuTableau(void){
    // pour des raisons de sécurité, on vérifie que nombreDeCases est un carré
   int index = 2;
   bool OK = false;  
   while (!OK && index++ <1000){
	if (nombreDeCases / index == index){
	    OK = true;
	}
   }
   if (!OK || nombreDeCases % index != 0){
	cout<<"apres "<<index<<" iterations, "<<nombreDeCases<<
		" n'est pas le carre de "<<index<<endl;
	exit (EXIT_FAILURE);
     }
    else coteDuTableau = index;
}
void Tableau::setEtatFinal(string aString){
   nombreDeCases = 0;
   char charRead ;
   string tempoString;
   int tempoStringToInt;
   do{
	charRead = aString.at(0); 
	aString.erase(0, 1);
	if ( charRead == separateur) {
	    stringstream(tempoString) >> tempoStringToInt;
	    EtatCourant.push_back(tempoStringToInt);
	    tempoString.clear();
	    nombreDeCases++;
	} 
	else tempoString += charRead;
    }
    while (!aString.empty());
    stringstream(tempoString) >> tempoStringToInt;
    EtatCourant.push_back(tempoStringToInt);
    nombreDeCases++;
    setCoteDuTableau();
    computeAbsoluteValue();
    Genealogie.append("@");
}
string Tableau::toString(){  
    char buffer [33];
    string aString = "Value = ";      
    aString += itoa(Value,buffer,10);
    aString += "\nAncetre = ";
    aString += Genealogie;
    aString += "\n";
    aString += getStringFromVectorInt(EtatCourant);
    aString += "\n";	
    return aString;
}
int Tableau::getDistanceTo(const Tableau &unTableau){
    int distance = 0;
    int maPosition;
    int saPosition; 
    //int coteDuCarre = sqrt(nombreDeCases);
    // DANGER Sécuriser cette conversion !!!!!!  
    // fait par Tableau::setCoteDuTableau(void)
    for(int i=0; i<EtatCourant.size(); i++){
	maPosition = EtatCourant.at(i);
	saPosition = unTableau.EtatCourant.at(i);
	distance = distance +
	   abs(maPosition / coteDuTableau -saPosition / coteDuTableau)
	  +abs(maPosition % coteDuTableau - saPosition % coteDuTableau);
    }
    return distance;  			
}
void Tableau::computeAbsoluteValue(void){
/*
 * somme de deux termes
 * une distance de type Manhattan
 * le nombre d'inversions dans EtatCourant privé de Zéro
 */
    int distance = 0;
    int maPosition; 
    for(int i=0; i<EtatCourant.size(); i++){
	maPosition = EtatCourant.at(i);
//	saPosition = i;
	distance = distance +
		 abs(maPosition / coteDuTableau -i / coteDuTableau)
	  +abs(maPosition % coteDuTableau - i % coteDuTableau);
    }  
    Value = distance + nbInversions(EtatCourant) ;
}
int Tableau::getValue(){
    return Value;
}
void Tableau::setGenealogie(string aString){
    Genealogie = aString;
}
string Tableau::getGenealogie(void){
    return Genealogie;
}
string Tableau::getStringFromVectorInt(const vector<int> vi){
    string aString ="";
    string idle = "";
    char buffer [33];
    for(int i = 0; i<nombreDeCases-1; i++){
	idle = itoa(vi[i],buffer,10);	
	aString += itoa(vi[i],buffer,10);
	if (i % coteDuTableau == coteDuTableau-1)
	    aString += "\n";
	else
	    aString += separateur;	    
    }
    aString += itoa(vi[nombreDeCases-1],buffer,10);	
    return aString;    
}
string Tableau::getHashKey(){
    return HashKey;
}
int Tableau::nbInversions(vector<int> v){
    int nbInvers = 0;
    for(int i=0; i<v.size();i++)
	for(int j = i+1; j<v.size();j++)
		if( v.at(i) > v.at(j)) nbInvers++;
    return nbInvers - positionZero(v);
}
int Tableau::positionZero(vector<int> v){
    int i = 0;
    while(v.at(i) != 0) ++i;
    return i;
}
Tableau Tableau::play(char coup){
     vector<int> vect = EtatCourant;
     int shift = coteDuTableau;

     int positionZero = 0;
     while(vect[positionZero] != 0 && positionZero < vect.size()) positionZero++;   
     char tempo = vect[positionZero];

     switch(coup){
	 case 'H':	vect[positionZero] = vect[positionZero-shift];
			vect[positionZero-shift] = tempo;
			break;
	 case 'G':	vect[positionZero] = vect[positionZero-1];
			vect[positionZero-1] = tempo;
			break;
	 case 'D':	vect[positionZero] = vect[positionZero+1];
			vect[positionZero+1] = tempo;
			break;
	 case 'B':	vect[positionZero] = vect[positionZero+shift];
			vect[positionZero+shift] = tempo;
			break;
	 default:	cout<<"erreur"<<endl;
     }
     Tableau tempoTableau(vect);
     return tempoTableau;    
}







