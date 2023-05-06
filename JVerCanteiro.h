#pragma once
#include "Janela.h"
#include "ListaCanteiros.h"
#include <wx/splitter.h>

/* Janela para acessar canteiros no sistema*/
class JVerCanteiro: public Janela
{
    private:
        ListaCanteiros* lC;
        wxSplitterWindow* splitter;

    public:
        
        JVerCanteiro(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
};