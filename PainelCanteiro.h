#pragma once
#include <wx/wx.h>
#include "Canteiro.h"

class PainelCanteiro: public wxPanel
{
    private:
        wxStaticText* nomeText, *especieText,*descricaoText,*phText,* umidadeText, *periodoText;
        wxTextCtrl* nome,*especie, *descricao;
        wxSlider* phSlider,*umidadeSlider,*periodoSlider;
        bool editavel;
    public:
        PainelCanteiro(wxWindow* parent,bool editavel= false);
        void AdicionarCanteiro(const DadosCanteiro canteiro);
        DadosCanteiro PegarCanteiro();
        void Reset();
        void MudarEstilo(bool editavel= false);
        void Atualizar();
        

};