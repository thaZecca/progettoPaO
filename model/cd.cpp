#include "./include/cd.hpp"

/*Costruttore parametrico di CD
@param tA puntatori a tracce audio da masterizzare nel CD
@param d diametro del CD in centimetri
@param s scaffale del CD
@param t titolo del CD*/
cd::cd(vector<audioD*> tA,float d, QString s, QString t): supportoMultimediale(s,t), tracceAudio(tA), diametro(d) {}

/*getTracceAudio
@return le tracce audio masterizzate nel CD*/
vector<contenutoMultimediale*> cd::getTracce() const{
    vector<contenutoMultimediale*> ret;
    for(auto it=tracceAudio.begin(); it!=tracceAudio.end(); it++){
        ret.push_back(*it);
    }
    return ret;
}

/*getDiametro
@return il diametro del CD in centimetri*/
float cd::getDiametro() const{
    return diametro;
}

/*setTracceAudio
@param tA tracce audio da rimasterizzare nel CD*/
void cd::setTracce(const vector<contenutoMultimediale*>& tA){
    for(auto it = tA.begin(); it != tA.end(); it++){
        audioD* a = dynamic_cast<audioD*>(*it);
        if(a) tracceAudio.push_back(a);
    }
}

/*setDiametro
@param d diametro da impostare al CD*/
void cd::setDiametro(float d){
    diametro=d;
}

/*accept - design pattern per accedere all'oggetto
@param v visitor*/
void cd::accept(visitorCMultimediale& v){
    v.visit(this);
}

/*getAutori
@return un vettore con tutti gli autori presenti nel cd*/
vector<QString> cd::getAutori() const{
    vector<QString> ret;
    for(auto it = tracceAudio.begin(); it != tracceAudio.end(); it++){
        const auto& autori = (*it) -> getAutori();
        for(auto& a : autori) ret.push_back(a);
    }
    return ret;
}

/*getAnno
@return un vettore con tutti gli anni di pubblicazione delle tracce del CD*/
vector<int> cd::getAnno() const{
    vector<int> ret;
    for(auto it = tracceAudio.begin(); it != tracceAudio.end(); it++){
        const auto& anno = (*it) -> getAnnoDiPubblicazione(); 
        ret.push_back(anno);
    }
    return ret;
}

/*operator<< esterno
@param os stream di output
@param c cd da stampare*/
ostream& operator<<(ostream& os, const cd& c){
    for(auto iterTa = c.tracceAudio.begin(); iterTa != c.tracceAudio.end(); iterTa++){
        os << *(*iterTa) << std::endl;
    }
    os << std::to_string(c.diametro) << "cm";
    return os;
}