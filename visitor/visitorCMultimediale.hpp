#ifndef VISITORCM_HPP
#define VISITORCM_HPP

class audioD;
class fileAudio;
class cd;
class videoD;
class fileVideo;
class dvd;
class contenutoMultimediale;

class visitorCMultimediale{
public:
    virtual void visitAudioD(audioD*) =0;
    virtual void visitFileAudio(fileAudio*) =0;
    virtual void visitCD(cd*) =0;
    virtual void visitVideoD(videoD*) =0;
    virtual void visitFileVideo(fileVideo*) =0;
    virtual void visitDVD(dvd*) =0;
};

#endif