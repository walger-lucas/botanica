#pragma once
#include "PainelCanteiro.h"
#include "Janela.h"

/*Janela para adicionar canteiro*/
class JAddCanteiro: public Janela
{
    private:
        PainelCanteiro* panel;
        void AddCanteiro(wxCommandEvent& event);
    public:
        JAddCanteiro(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);

        wxDECLARE_EVENT_TABLE();
};