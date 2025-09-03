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

/*submitQuery - slot che ridireziona la query
@param q query*/
void ItemView::submitQuery(query q){
    prepare(&q);
}

/*filter - filtra i contenuti multimeidali e i supporti multimediali a seconda della query
@param q query 
#param cM vettore di contenuti multimediali
@param sM vettore di supporti multimediali*/
void ItemView::filter(query* q, vector<contenutoMultimediale*>& cM, vector<supportoMultimediale*>& sM){
    //filtro per contenuto multimediale
    for (auto it = cM.begin(); it != cM.end();){
        bool keep = true;

        //filtro di tipo
        auto* ptr = *it;
        if (q->getType() == "Audio digitale" && typeid(*ptr) != typeid(audioD)) keep = false;
        else if (q->getType() == "File Audio" && typeid(*ptr) != typeid(fileAudio)) keep = false;
        else if (q->getType() == "File Video" && typeid(*ptr) != typeid(fileVideo)) keep = false;
        else if (q->getType() == "Video digitale" && typeid(*ptr) != typeid(videoD)) keep = false;
        else if (q->getType() == "CD" && typeid(*ptr) != typeid(cd)) keep = false;
        else if (q->getType() == "DVD" && typeid(*ptr) != typeid(dvd)) keep = false;

        //se il tipo non corrisponde, lo elimino subito
        if (!keep){
            it = cM.erase(it);
            continue;
        }

        //check filtri aggiuntivi solo se almeno uno selezionato
        bool filterActive = q->getCheckTitle() || q->getCheckArtist() || q->getCheckYear();
        if (filterActive){
            bool matched = false;

            //titolo
            if (q->getCheckTitle() && (*it)->getTitolo().contains(q->getText(), Qt::CaseInsensitive))
                matched = true;

            //autore
            if (!matched && q->getCheckArtist()){
                for (auto& a : (*it)->getAutori()){
                    if (a.contains(q->getText(), Qt::CaseInsensitive)){
                        matched = true;
                        break;
                    }
                }
            }

            //anno
            if (!matched && q->getCheckYear()){
                if (static_cast<int>((*it)->getAnnoDiPubblicazione()) == q->getText().toInt()) matched = true;
            }
            //controllo se ha superato almeno una dei tre match
            if (!matched) keep = false;
        }
        //scelta finale
        if (!keep) cM.erase(it);
        else it++;
    }
    //filtro per supporto multimediale
    for (auto it = sM.begin(); it != sM.end();){
        bool keep = true;

        //filtro di tipo
        auto* ptr = *it;
        if (q->getType() == "Audio digitale" && typeid(*ptr) != typeid(audioD)) keep = false;
        else if (q->getType() == "File Audio" && typeid(*ptr) != typeid(fileAudio)) keep = false;
        else if (q->getType() == "File Video" && typeid(*ptr) != typeid(fileVideo)) keep = false;
        else if (q->getType() == "Video digitale" && typeid(*ptr) != typeid(videoD)) keep = false;
        else if (q->getType() == "CD" && typeid(*ptr) != typeid(cd)) keep = false;
        else if (q->getType() == "DVD" && typeid(*ptr) != typeid(dvd)) keep = false;

        //se il tipo non corrisponde, lo elimino subito
        if (!keep){
            it = sM.erase(it);
            continue;
        }

        //check filtri aggiuntivi solo se almeno uno selezionato
        bool filterActive = q->getCheckTitle() || q->getCheckArtist() || q->getCheckYear();
        if (filterActive) {
            bool matched = false;

            //titolo
            if (q->getCheckTitle() && (*it)->getTitolo().contains(q->getText(), Qt::CaseInsensitive))
                matched = true;

            //autore
            if (!matched && q->getCheckArtist()){
                for (auto& a : (*it)->getAutori()){
                    if (a.contains(q->getText(), Qt::CaseInsensitive)){
                        matched = true;
                        break;
                    }
                }
            }

            //anno
            if (!matched && q->getCheckYear()){
                vector<int> anni = (*it) -> getAnno();
                for(auto y = anni.begin(); y != anni.end(); y++)
                    if (*y == q->getText().toInt()) matched = true;
            }
            //controllo se ha superato almeno una dei tre match
            if (!matched) keep = false;
        }
        //decisione finale
        if (!keep) sM.erase(it);
        else it++;
    }

}
