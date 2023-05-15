#pragma once
#include "Janela.h"
#include "ListaCanteiros.h"
#include "PainelRelatorio.h"
#include "Canteiro.h"

/* Janela para adicionar Relatório*/
class JAddRelatorio: public Janela
{
        bool segundaPag=false;
        ListaCanteiros* lC;
        PainelRelatorio* relatorios;
        wxButton* adicionarRelatorio;
        idCanteiros id=CANTEIRO_NULO;
    public:
        void Select(wxCommandEvent& event);
        void SelecionarCanteiro(idCanteiros& _id);
        JAddRelatorio(GerenciadorJanelas* gJ,wxWindow* parent);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);
        wxDECLARE_EVENT_TABLE();
};