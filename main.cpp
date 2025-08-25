#include "./model/include/audioD.hpp"
#include "./modules/include/contenutoMultimediale.hpp"
#include "./visitor/include/fileManager.hpp"
#include <QString>
#include <vector>
#include <iostream>

using std::vector;

int main(){
    vector<QString> a;
    a.push_back("Dire Straits");
    audioD* sos = new audioD("Sultans of Swing", "Vertigo Records", a, 1978, 240, "provapP", 100, 44100, true, 2);
    
    vector<contenutoMultimediale*> cm;
    cm.push_back(sos);

    vector<contenutoMultimediale*> vuoto;

    fileManager manager();

    manager.save(cm, vuoto);

    return 0;
}