#include "JAddRelatorio.h"

JAddRelatorio::JAddRelatorio(GerenciadorJanelas* gJ, wxWindow* parent)
: Janela(gJ,parent,wxID_ANY)
{
    
    lC = new ListaCanteiros(this);
    lC->SetBackgroundColour(wxColor(100,200,200));
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(lC,1,wxEXPAND|wxALL);
    wxButton* button = new wxButton(lC,-1,L"Adicionar Relatório");
    lC->GetSizer()->Add(button,0.3,wxEXPAND|wxALL,10);
}

void JAddRelatorio::Inicializar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_RELATORIO,false);
    jP->SetStatusText(L"Cadastrar relatório a um canteiro cadastrado no sistema.");
    
}

void JAddRelatorio::Desligar(JanelaPrincipal* jP)
{
    jP->GetMenuBar()->Enable(MenuID::ID_NEW_RELATORIO,true);
}