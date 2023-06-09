#pragma once
#include "Janela.h"
#include "ListaCanteiros.h"
#include "PainelCanteiro.h"
#include "JAddRelatorio.h"
#include "JVerRelatorio.h"
#include <wx/splitter.h>

/* Janela para acessar canteiros no sistema*/
class JVerCanteiro: public Janela
{
    private:
        JAddRelatorio* jRel;
        JVerRelatorio* jvRel;
        ListaCanteiros* lC; //painel esquerdo
        PainelCanteiro* painelCanteiro;
        wxPanel* direito;//painel direito
        wxPanel* botoes;
        wxSplitterWindow* splitter;
        idCanteiros idSelecionado;

        wxButton* botaoDeletar;
        wxButton* botaoAcessarRelatorio;
        wxButton* botaoAdicionarRelatorio;
        
        void DeleteCanteiro(wxCommandEvent& event);
        void Select(wxCommandEvent& event);
        void AddRelatorio(wxCommandEvent& event);
        void VerRelatorio(wxCommandEvent& evt);
    public:
        
        JVerCanteiro(GerenciadorJanelas* gJ,wxWindow* parent,JAddRelatorio* jRel,JVerRelatorio* jvRel);
        void Inicializar(JanelaPrincipal* jP);
        void Desligar(JanelaPrincipal* jP);

        wxDECLARE_EVENT_TABLE();
        
};