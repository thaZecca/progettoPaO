#include "./include/dvd.hpp"

/*costruttore parametrico completo di DVD
@param tV puntatori a tracce videoD da masterizzare nel DVD
@param s scaffale del DVD
@param d diametro del DVD*/
dvd::dvd(vector<videoD*> tV, float d, QString s): supportoMultimediale(s), tracceVideo(tV), diametro(d) {}

/*getTracceVideo
@return le tracce video masterizzate nel DVD*/
vector<contenutoMultimediale*> dvd::getTracce() const{
    vector<contenutoMultimediale*> ret;
    for(auto it = tracceVideo.begin(); it != tracceVideo.end(); it++){
        ret.push_back(*it);
    }
    return ret;
}

/*getDiametro
@return il diametro del DVD*/
float dvd::getDiametro() const{
    return diametro;
}

/*setTracceVideo
@param tV tracce video da masterizzare nel DVD*/
void dvd::setTracce(const vector<contenutoMultimediale*>& tV){
    for(auto it = tV.begin(); it != tV.end(); it++){
        videoD* v = dynamic_cast<videoD*>(*it);
        if(v) tracceVideo.push_back(v);
    }
}

/*setDiametro
@param d diametro da impostare al DVD*/
void dvd::setDiametro(float d){
    diametro = d;
}

/*accept - design pattern per accedere all'oggetto
@param v visitor*/
void dvd::accept(visitorCMultimediale& v){
    v.visit(this);
}

/*operator<< esterno
@param os stream di output
@param d dvd da stampare*/
ostream& operator<<(ostream& os, const dvd& d){
    for(auto iter = d.tracceVideo.begin(); iter != d.tracceVideo.end(); iter++){
        os << *(*iter) << std::endl;
    }
    os << d.diametro << "cm";
    return os;
}