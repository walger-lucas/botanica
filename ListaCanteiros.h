#pragma once
#include <wx/wx.h>

class ListaCanteiros: public wxPanel
{

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
    private:
        wxTextCtrl* text= nullptr;
        wxListBox* list= nullptr;
        
};