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
    virtual void visit(audioD*) =0;
    virtual void visit(fileAudio*) =0;
    virtual void visit(cd*) =0;
    virtual void visit(videoD*) =0;
    virtual void visit(fileVideo*) =0;
    virtual void visit(dvd*) =0;
};

#endif