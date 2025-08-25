#ifndef VISITORCM_HPP
#define VISITORCM_HPP

class audioD;
class fileAudio;
class cd;
class videoD;
class fileVideo;
class dvd;

class visitorCMultimediale{
public:
    virtual void visitAudioD(audioD*);
    virtual void visitFileAudio(fileAudio*);
    virtual void visitCD(cd*);
    virtual void visitVideoD(videoD*);
    virtual void visitFileVideo(fileVideo*);
    virtual void visitDVD(dvd*);
};

#endif