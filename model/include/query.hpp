#ifndef QUERY_HPP
#define QUERY_HPP

#include <QString>
#include "contenutoMultimediale.hpp"
#include "supportoMultimediale.hpp"
#include "audioD.hpp"
#include "cd.hpp"
#include "dvd.hpp"
#include "fileAudio.hpp"
#include "fileVideo.hpp"
#include "videoD.hpp"

/*query -  classe mesaggera delle query nella SearchView*/
class query{
private:
    QString text;
    QString type;
    bool checkTitle;
    bool checkArtist;
    bool checkYear;
public:
    query(const QString&, const QString&, bool, bool, bool);
    QString getText() const;
    QString getType() const;
    bool getCheckTitle() const;
    bool getCheckArtist() const;
    bool getCheckYear() const;
    //al momento non prevedo metodi setter. 
    
    void filter(vector<contenutoMultimediale*>&, vector<supportoMultimediale*>&);
};

#endif