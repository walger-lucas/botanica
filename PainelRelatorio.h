#pragma once
#include <wx/wx.h>
#include "Relatorio.h"

class PainelRelatorio: public wxPanel
{
    private:
        wxStaticText* estadoText,*descricaoText,*phText,* umidadeText;
        wxTextCtrl*estado, *descricao;
        wxSlider* phSlider,*umidadeSlider;
        bool editavel;
    public:
        PainelRelatorio(wxWindow* parent,bool editavel= false);
        void AdicionarRelatorio(const DadosRelatorio canteiro);
        DadosRelatorio PegarRelatorio();
        void Reset();
        void MudarEstilo(bool editavel= false);
        void Atualizar();
        

};