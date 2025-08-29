#include "./model/include/audioD.hpp"
#include "./model/include/videoD.hpp"
#include "./model/include/cd.hpp"
#include "./model/include/dvd.hpp"
#include "./model/include/fileAudio.hpp"
#include "./model/include/fileVideo.hpp"
#include "./model/include/contenutoMultimediale.hpp"
#include "./fileManager/include/fileManager.hpp"
#include <QString>
#include <vector>
#include <iostream>
#include <QApplication>
#include <QDir>

using std::vector;

int main(int argc, char* argv[]){
    QApplication app(argc,argv);

    QDir dir(QCoreApplication::applicationDirPath());
    #if defined(Q_OS_MAC)
        dir.cdUp(); dir.cdUp(); dir.cdUp();
    #else
        dir.cdUp();
    #endif
    QString path = dir.filePath("storage.json");
    /*
    vector<QString> a;
    a.push_back("Dire Straits");
    audioD* sos = new audioD("Sultans of Swing", "Vertigo Records", a, 1978, 240, "provapP", 100, 44100, true, 2);

    a.push_back("Sting");
    fileAudio* mfn = new fileAudio("Money fo Nothing", "Vertigo Records", a, 1978, 240, "provapP", 100, 44100, true, 2, false, "flac");

    vector<audioD*> audio;
    
    audioD* mib = new audioD("Message in a bottle", "MJD Records", {"The Police"}, 1977, 240, "pppolice", 1000, 44100, true, 2);
    audio.push_back(mib);
    audio.push_back(sos);

    videoD* police = new videoD("Message in a bottle - Video", "MJD Videos", {"Sting", "Andy Summers", "Steve Copland"}, 1977, 240, "pppolice", 1000, 60, true, "1920");
    videoD* police2 = new videoD("Message in a bottle - Video", "MJD Videos", {"Sting", "Andy Summers", "Steve Copland"}, 1977, 240, "pppolice", 1000, 60, true, "1920");

    fileVideo* sff = new fileVideo("Strawberry fields forever - Video", "Apple Corps", {"Paul McCartney", "John Lennon", "George Harrison", "Ringo Starr"}, 1967, 240, "ppbeatles", 1000, 60, true, "1920", "mp4");
    fileVideo* sff2 = new fileVideo("Strawberry fields forever - Video", "Apple Corps", {"Paul McCartney", "John Lennon", "George Harrison", "Ringo Starr"}, 1967, 240, "ppbeatles", 1000, 60, true, "1920", "mp4");

    cd* compilation = new cd(audio, 12, "5A2");

    dvd* MTV = new dvd({police2, sff2}, 12, "6A2");
    MTV -> setInPrestito(true);
    MTV -> setDataPrestito(QDate(2025,8,29));
    MTV -> setDurataPrestito(7);
    MTV -> setNomePrestito("Simone");
    
    vector<contenutoMultimediale*> cm;
    cm.push_back(sos);
    cm.push_back(mfn);

    police -> setInPrestito(true);
    police -> setDataPrestito(QDate(2025,8,29));
    police -> setDurataPrestito(7);
    police -> setNomePrestito("Simone");

    sff -> setInPrestito(true);
    sff -> setDataPrestito(QDate(2025,8,22));
    sff -> setDurataPrestito(7);
    sff -> setNomePrestito("Clara");

    cm.push_back(police);
    cm.push_back(sff);*/

    fileManager manager(path);

    //manager.save(cm, {compilation, MTV});

    vector<contenutoMultimediale*> uno;
    vector<supportoMultimediale*> due;

    manager.load(uno,due);

    for(auto i=uno.begin(); i!=uno.end(); i++)
        std::cout << *(*i) << std::endl;

    for(auto i=due.begin(); i!=due.end(); i++)
        std::cout << (*i) << std::endl;

    return 0;
}