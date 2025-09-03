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