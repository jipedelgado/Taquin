
#include "Taquin.h"

Taquin::Taquin(){
   // widget.setupUi(this);    
 }
Taquin::Taquin(int s) {
   // widget.setupUi(this);
    Size = s;
}
Taquin::Taquin(string s){
  //  widget.setupUi(this);
    EtatFinal.setEtatFinal(s);
    EtatInitial = EtatFinal;
    Stack.push(EtatFinal);
}
Taquin::Taquin(int size, string aString){
    EtatFinal.coteDuTableau = size;
    EtatFinal.setEtatFinal(aString);
    Size = EtatFinal.coteDuTableau;
    Stack.push(EtatFinal);
}
void Taquin::setTaquin(string aString) {
    EtatFinal.setEtatFinal(aString);
    Size = EtatFinal.coteDuTableau;
    Stack.push(EtatFinal);
}
Taquin::~Taquin() {
}

void Taquin::compute( Tableau& tableau, int count){
 // count sert à empecher un débordement, voir AVERTISSEMENT en en-tete de main.cpp
   EtatFinal = tableau;
   try{
     Stack.pop();
     if ( count > 0 && tableau.Value >0) {
         Tableau TableauCourant = tableau;
         vector<Tableau> vectorTempo = TableauCourant.Fils();

         for(size_t i = 0; i<vectorTempo.size();i++){
             //on recherche si TableauCourant[i] a déjà été atteint
             unordered_set<string>::const_iterator got = EnsembleExplore.find(vectorTempo.at(i).getHashKey());
             if(got == EnsembleExplore.end()) // TableauCourant[i] n'a jamais été atteint
               {
                 Stack.push(vectorTempo.at(i));
                 EnsembleExplore.insert(vectorTempo.at(i).getHashKey());
               }
         }

         if(Stack.size()> 20659){
            cout<<"Stack Overflow : Stack.size > "<<Stack.size()<<endl;
            cout<<"# suite en cours  = "<<EtatFinal.toString()<<endl;
            exit(EXIT_FAILURE);
         }
         TableauCourant = Stack.top();
         nbEtatsTraites++;
         compute(TableauCourant,--count);
       }
   }
   catch(exception& e){
     cout << "An exception occurred. Exception Nr. " << e.what() << '\n';
   }
}


int Taquin::parite(vector<int> v){
    int nbInversions = 0;
    for(size_t i=0; i<v.size();i++)
        for(size_t j = i+1; j<v.size();j++)
		if( v.at(i) > v.at(j)) nbInversions++;
    return nbInversions - positionZero(v);
}
int Taquin::positionZero(vector<int> v){
    int i = 0;
    while(v.at(i) != 0) ++i;
    return i;
}
vector<int> Taquin::wrap(vector<int> v, int pas){
    vector<int> tempo = v;
    int debug = 0;
    int deltaDebug = 0;
    for(size_t k=0; k<v.size();k++){
	if( k % pas == 0 && k!=0) deltaDebug = pas;
	else deltaDebug = 1-2*((k/pas)%2);	
	debug += deltaDebug;
	tempo[k] = v.at(debug-1);
    }
    return tempo;
}
string Taquin::getStringFromVectorInt(const vector<int> vi, size_t nombreDeCases, size_t coteDuTableau){
    string aString ="";
    string idle = "";
    char buffer [33];
    for(size_t i = 0; i<nombreDeCases-1; i++){
	idle = itoa(vi[i],buffer,10);	
	aString += itoa(vi[i],buffer,10);
	if (i % coteDuTableau == coteDuTableau-1)
	    aString += "\n";
	else
	    aString += " ";	    
    }
    aString += itoa(vi[nombreDeCases-1],buffer,10);
	
    return aString;    
}
vector<Tableau> Taquin::SuiteDeCoupsGagnants(string suiteDeCoups){
/* sans contrôle d'erreur, cette procedure ne s'applique qu'avec
 * une string generee par l'algorithme de recherche de solutions conformes
 * */
    vector<Tableau> vecteurTableau;
    Tableau tempoTableau = EtatInitial;
    for(size_t i = 1; i<suiteDeCoups.size();i++){
	tempoTableau = tempoTableau.play(suiteDeCoups.at(i));
	tempoTableau.Genealogie = suiteDeCoups.at(i);
	vecteurTableau.push_back(tempoTableau);
    }
    return vecteurTableau;
}



