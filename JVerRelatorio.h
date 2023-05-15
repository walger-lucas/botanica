#pragma once
#include "Janela.h"
#include "ListaCanteiros.h"
#include "PainelRelatorio.h"
#include <wx/wx.h>
#include <wx/splitter.h> 

class JVerRelatorio: public Janela
{
    wxSplitterWindow* splitter;
    ListaCanteiros* lC;
    wxListBox* listRelat;
    idCanteiros idCant;
    PainelRelatorio* pRelatorios;
    void Select(wxCommandEvent& event);
    void SelectRelatorio(wxCommandEvent& event);
    public:
        JVerRelatorio(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
    
    wxDECLARE_EVENT_TABLE();
};