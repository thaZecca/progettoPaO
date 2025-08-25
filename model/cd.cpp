#include "./include/cd.hpp"

/*Costruttore parametrico di CD
@param tA tracce audio da masterizzare nel CD
@param d diametro del CD in centimetri*/
cd::cd(vector<audioD> tA,float d): tracceAudio(tA), diametro(d) {}

/*getTracceAudio
@return le tracce audio masterizzate nel CD*/
vector<audioD> cd::getTracceAudio() const{
    return tracceAudio;
}

/*getDiametro
@return il diametro del CD in centimetri*/
float cd::getDiametro() const{
    return diametro;
}

/*setTracceAudio
@param tA tracce audio da rimasterizzare nel CD*/
void cd::setTracceAudio(vector<audioD>& tA){
    tracceAudio=tA;
}

/*setDiametro
@param d diametro da impostare al CD*/
void cd::setDiametro(float d){
    diametro=d;
}

void cd::accept(visitorCMultimediale& v){
    v.visit(this);
}

ostream& operator<<(ostream& os, const cd& c){
    for(auto iterTa = c.tracceAudio.begin(); iterTa != c.tracceAudio.end(); iterTa++){
        os << (*iterTa) << std::endl;
    }
    os << std::to_string(c.diametro) << "cm";
    return os;
}