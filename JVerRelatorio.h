#pragma once
#include "Janela.h"
#include "ListaCanteiros.h"
#include <wx/wx.h>
#include <wx/splitter.h> 

class JVerRelatorio: public Janela
{
    wxSplitterWindow* splitter;
    ListaCanteiros* lC;
    
    public:
        JVerRelatorio(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};