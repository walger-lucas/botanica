#pragma once
#include <wx/wx.h>

class PainelCanteiro: public wxPanel
{
    private:
        wxStaticText* nomeText, *especieText,*descricaoText,*phText,* umidadeText;
        wxTextCtrl* nome,*especie, *descricao;
        wxSlider* phSlider,*umidadeSlider;
        bool editavel;
    public:
        PainelCanteiro(wxWindow* parent,bool editavel= false);
        void Reset();
        void MudarEstilo(bool editavel= false);
        void Atualizar();
        

};