#include "include/query.hpp"

/*Costruttore parametrico completo di classe query
@param tx texto della query
@param ty tipo scelto per la query
@param isCT true se checkbox titolo cliccata, false altrimenti
@param isCA true se checkbox artista cliccata, false altrimenti
@param isCY true se checkbox anno cliccata, false altrimenti*/
query::query(const QString& tx, const QString& ty, bool isCT, bool isCA, bool isCY): text(tx), type(ty), checkTitle(isCT), checkArtist(isCA), checkYear(isCY) {}

/*getText
@return il testo della query*/
QString query::getText() const{
    return text;
}

/*getType
@return il tipo scelto nella query*/
QString query::getType() const{
    return type;
}

/*getCheckTitle
@return true se checkbox titolo cliccata, false altrimenti*/
bool query::getCheckTitle() const{
    return checkTitle;
}

/*getCheckArtist
@return true se checkbox artista cliccata, false altrimenti*/
bool query::getCheckArtist() const{
    return checkArtist;
}

/*getCheckYear
@return true se checkbox anno cliccata, false altrimenti*/
bool query::getCheckYear() const{
    return checkYear;
}

/*filter - filtra i contenuti multimeidali e i supporti multimediali a seconda della query
@param cM vettore di contenuti multimediali
@param sM vettore di supporti multimediali*/
void query::filter(vector<contenutoMultimediale*>& cM, vector<supportoMultimediale*>& sM){
    //filtro per contenuto multimediale
    for (auto it = cM.begin(); it != cM.end();){
        bool keep = true;

        //filtro di tipo
        auto* ptr = *it;
        if (type == "Audio digitale" && typeid(*ptr) != typeid(audioD)) keep = false;
        else if (type == "File Audio" && typeid(*ptr) != typeid(fileAudio)) keep = false;
        else if (type == "File Video" && typeid(*ptr) != typeid(fileVideo)) keep = false;
        else if (type == "Video digitale" && typeid(*ptr) != typeid(videoD)) keep = false;
        else if (type == "CD" && typeid(*ptr) != typeid(cd)) keep = false;
        else if (type == "DVD" && typeid(*ptr) != typeid(dvd)) keep = false;

        //se il tipo non corrisponde, lo elimino subito
        if (!keep){
            it = cM.erase(it);
            continue;
        }

        //check filtri aggiuntivi solo se almeno uno selezionato
        bool filterActive = checkTitle || checkArtist || checkYear;
        if (filterActive){
            bool matched = false;

            //titolo
            if (checkTitle && (*it)->getTitolo().contains(text, Qt::CaseInsensitive))
                matched = true;

            //autore
            if (!matched && checkArtist){
                for (auto& a : (*it)->getAutori()){
                    if (a.contains(text, Qt::CaseInsensitive)){
                        matched = true;
                        break;
                    }
                }
            }

            //anno
            if (!matched && checkYear){
                if (static_cast<int>((*it)->getAnnoDiPubblicazione()) == text.toInt()) matched = true;
            }
            //controllo se ha superato almeno una dei tre match
            if (!matched) keep = false;
        }
        //scelta finale
        if (!keep) cM.erase(it);
        else it++;
    }
    //filtro per supporto multimediale
    for (auto it = sM.begin(); it != sM.end();){
        bool keep = true;

        //filtro di tipo
        auto* ptr = *it;
        if (type == "Audio digitale" && typeid(*ptr) != typeid(audioD)) keep = false;
        else if (type == "File Audio" && typeid(*ptr) != typeid(fileAudio)) keep = false;
        else if (type == "File Video" && typeid(*ptr) != typeid(fileVideo)) keep = false;
        else if (type == "Video digitale" && typeid(*ptr) != typeid(videoD)) keep = false;
        else if (type == "CD" && typeid(*ptr) != typeid(cd)) keep = false;
        else if (type == "DVD" && typeid(*ptr) != typeid(dvd)) keep = false;

        //se il tipo non corrisponde, lo elimino subito
        if (!keep){
            it = sM.erase(it);
            continue;
        }

        //check filtri aggiuntivi solo se almeno uno selezionato
        bool filterActive = checkTitle || checkArtist || checkYear;
        if (filterActive) {
            bool matched = false;

            //titolo
            if (checkTitle && (*it)->getTitolo().contains(text, Qt::CaseInsensitive))
                matched = true;

            //autore
            if (!matched && checkArtist){
                for (auto& a : (*it)->getAutori()){
                    if (a.contains(text, Qt::CaseInsensitive)){
                        matched = true;
                        break;
                    }
                }
            }

            //anno
            if (!matched && checkYear){
                vector<int> anni = (*it) -> getAnno();
                for(auto y = anni.begin(); y != anni.end(); y++)
                    if (*y == text.toInt()) matched = true;
            }
            //controllo se ha superato almeno una dei tre match
            if (!matched) keep = false;
        }
        //decisione finale
        if (!keep) sM.erase(it);
        else it++;
    }

}