#ifndef VISITORCM_HPP
#define VISITORCM_HPP

class visitorCMultimediale{
public:
    virtual void visitAudioD(const audioD&) = 0;
    virtual void visitVideoD(const videoD&) = 0;
    virtual void visitFileAudio(const fileAudio&) = 0;
    virtual void visitFileVideo(const fileVideo&) = 0;
};

#endif