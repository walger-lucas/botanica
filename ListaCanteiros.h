#pragma once
#include <wx/wx.h>
#include "Canteiro.h"

class ListaCanteiros: public wxPanel
{

    private:
        wxTextCtrl* text= nullptr;
        wxListBox* list= nullptr;
        wxDECLARE_EVENT_TABLE();
    public:
        enum IDs
        {
            ID_TEXT = 6,
            ID_SELECT
        };
        long idSelected;
        ListaCanteiros(wxWindow* parent);
        void ResetText();
        idCanteiros GetIdCanteiro();
        void Select(string nome);
        void Atualizar();
        void AtualizarTexto(wxCommandEvent& event);
        
};