#ifndef QUERY_HPP
#define QUERY_HPP

#include <QString>

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
};

#endif