#pragma once
#include <wx/wx.h>

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
        void Select(long ID);
        void Atualizar();
        void AtualizarTexto(wxCommandEvent& event);
        
};