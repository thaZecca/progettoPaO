#include "./include/dvd.hpp"

/*costruttore parametrico completo di DVD
@param tV tracce video da masterizzare nel DVD
@param d diametro del DVD*/
dvd::dvd(vector<videoD> tV, float d): tracceVideo(tV), diametro(d) {}

/*getTracceVideo
@return le tracce video masterizzate nel DVD*/
vector<videoD> dvd::getTracceVideo() const{
    return tracceVideo;
}

/*getDiametro
@return il diametro del DVD*/
float dvd::getDiametro() const{
    return diametro;
}

/*setTracceVideo
@param tV tracce video da masterizzare nel DVD*/
void dvd::setTracceVideo(vector<videoD>& tV){
    tracceVideo = tV;
}

/*setDiametro
@param d diametro da impostare al DVD*/
void dvd::setDiametro(float d){
    diametro = d;
}

ostream& operator<<(ostream& os, const dvd& d){
    for(auto iter = d.tracceVideo.begin(); iter != d.tracceVideo.end(); iter++){
        os << (*iter) << std::endl;
    }
    os << d.diametro << "cm";
    return os;
}