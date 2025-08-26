#include "./model/include/audioD.hpp"
#include "./model/include/cd.hpp"
#include "./model/include/fileAudio.hpp"
#include "./model/include/contenutoMultimediale.hpp"
#include "./visitor/include/fileManager.hpp"
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

    vector<QString> a;
    a.push_back("Dire Straits");
    audioD* sos = new audioD("Sultans of Swing", "Vertigo Records", a, 1978, 240, "provapP", 100, 44100, true, 2);

    a.push_back("Sting");
    fileAudio* mfn = new fileAudio("Money fo Nothing", "Vertigo Records", a, 1978, 240, "provapP", 100, 44100, true, 2, false, "flac");

    vector<audioD*> audio;
    
    audioD* mib = new audioD("Message in a bottle", "MJD Records", {"The Police"}, 1977, 240, "pppolice", 1000, 44100, true, 2);
    audio.push_back(mib);
    audio.push_back(sos);

    cd* compilation = new cd(audio, 12);
    
    vector<contenutoMultimediale*> cm;
    cm.push_back(sos);
    cm.push_back(mfn);

    vector<contenutoMultimediale*> vuoto;

    fileManager manager(path);

    manager.save(cm, vuoto, {compilation}, {});

    return 0;
}