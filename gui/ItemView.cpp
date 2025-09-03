#include "include/ItemView.hpp"

/*Costruttore parametrico
@param parent*/
ItemView::ItemView(QWidget* parent): QScrollArea(parent){
    setWidgetResizable(true); //ridimensionamento automatico
    prepare(); //preparo il widget delle previews nella scrollbar area
}

/*prepare - prepara l'interfaccia di item a seconda del visitor
@param v visitor*/
void ItemView::prepare(query* q){
    PreviewVisitor v; //visitor che crea la preview per ogni item
    setWidget(nullptr); //libera la memoria occupata dal vecchio widget

    QWidget* previews = new QWidget(); //QWidget che contiene tutte le preview
    QVBoxLayout* previewLayout = new QVBoxLayout(previews); //layout per il widget totale

    vector<contenutoMultimediale*> con = biblioteca::instance().getContenuti();
    vector<supportoMultimediale*> sup = biblioteca::instance().getSupporti();

    if(q) filter(q,con,sup);

    //aggiungo al layout ogni preview di contenutoMultimediale
    for(auto c = con.begin(); c != con.end(); c++){
        (*c) -> accept(v);
        previewLayout -> addWidget(v.getPreview());
    }
    for(auto s = sup.begin(); s != sup.end(); s++){
        (*s) -> accept(v);
        previewLayout -> addWidget(v.getPreview());
    }
    previewLayout -> addStretch(); //stretcho il layout totale
    setWidget(previews);
}

void ItemView::submitQuery(query q){
    prepare(&q);
}

void ItemView::filter(query* q, vector<contenutoMultimediale*>& cM, vector<supportoMultimediale*>& sM){
    if(q -> getType() == "Audio digitale"){
        for(auto it = cM.begin(); it != cM.end();){
            auto ptr = *it;
            if(typeid(*ptr)!=typeid(audioD)) cM.erase(it);
            else it++;
        }
        for(auto it = sM.begin(); it != sM.end();){
            sM.erase(it);
        }
    }else if(q -> getType() == "CD"){
        for(auto it = cM.begin(); it != cM.end();){
            cM.erase(it);
        }
        for(auto it = sM.begin(); it != sM.end();){
            auto ptr = *it;
            if(typeid(*ptr)!=typeid(cd)) sM.erase(it);
            else it++;
        }
    }else if(q -> getType() == "DVD"){
        for(auto it = cM.begin(); it != cM.end();){
            cM.erase(it);
        }
        for(auto it = sM.begin(); it != sM.end();){
            auto ptr = *it;
            if(typeid(*ptr)!=typeid(dvd)) sM.erase(it);
            else it++;
        }
    }else if(q -> getType() == "File Audio"){
        for(auto it = cM.begin(); it != cM.end();){
            auto ptr = *it;
            if(typeid(*ptr)!=typeid(fileAudio)) cM.erase(it);
            else it++;
        }
        for(auto it = sM.begin(); it != sM.end();){
            sM.erase(it);
        }
    }else if(q -> getType() == "File Video"){
        for(auto it = cM.begin(); it != cM.end();){
            auto ptr = *it;
            if(typeid(*ptr)!=typeid(fileVideo)) cM.erase(it);
            else it++;
        }
        for(auto it = sM.begin(); it != sM.end();){
            sM.erase(it);
        }
    }else if(q -> getType() == "Video digitale"){
        for(auto it = cM.begin(); it != cM.end();){
            auto ptr = *it;
            if(typeid(*ptr)!=typeid(videoD)) cM.erase(it);
            else it++;
        }
        for(auto it = sM.begin(); it != sM.end();){
            sM.erase(it);
        }
    }
}
