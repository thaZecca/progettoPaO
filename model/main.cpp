#include "./include/audioD.hpp"
#include "./include/fileAudio.hpp"
#include "./include/videoD.hpp"
#include "./include/fileVideo.hpp"
#include "./include/cd.hpp"
#include "./include/dvd.hpp"
#include <QString>
#include <vector>
#include <iostream>

int main(){
    vector<QString> a;
    a.push_back("Dire Straits");
    audioD* sos = new audioD("Sultans of Swing", "Vertigo Records", a, 1978, 240, "provapP", 100, 44100, true, 2);
    vector<QString> s;
    s.push_back("Simone Zecchinato");
    s.push_back("Pietro Pegoraro");
    fileAudio* fA = new fileAudio("Settembre", "Wave Records", s, 2025, 240, "C:/ciao/img.png", 200, 44100, true, 2, false, "flac");
    //std::cout << *sos << std::endl;
    //std::cout << *fA << std::endl;
    //std::cout << std::endl;
    videoD* vid = new videoD("Video settembre", "Wave Videos", s, 2025, 240, "C:/ciao/img.png", 1000, 60, true, "1080");
    videoD* vid2 = new videoD("Money for Nothing - video", "Vertigo Records", a, 1980, 240, "C://prova/p.png", 1000, 60, true, "720");
    //std::cout << *vid << std::endl;
    //fileVideo* fv = new fileVideo("Video Sultans of Swing", "Vertigo Videos", a, 1978, 240, "provapPp", 1000, 30, false, "1080", "mp4");
    //std::cout << *fv << std::endl;
    a.push_back("Sting");
    audioD* mfn = new audioD("Money for Nothing", "Vertigo Records", a, 1980, 240, "provaP2", 100, 44100, true, 2);
    vector<audioD> tracce;
    tracce.push_back(*sos);
    tracce.push_back(*mfn);
    cd* direst = new cd(tracce, 5);

    vector<videoD> tracceVideo;
    tracceVideo.push_back(*vid);
    tracceVideo.push_back(*vid2);

    dvd* caso = new dvd(tracceVideo, 12);
    std::cout << *caso << std::endl;


    //std::cout << *direst << std::endl;
    return 0;
}